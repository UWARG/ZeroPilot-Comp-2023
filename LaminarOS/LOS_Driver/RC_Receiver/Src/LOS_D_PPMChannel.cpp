#include "LOS_D_PPMChannel.hpp"
#include "tim.h"
#include "RSSI.hpp"

PPMChannel::PPMChannel(TIM_HandleTypeDef* timer, uint16_t timer_channel, uint8_t num_channels): timer_(timer),
																								timer_channel_(timer_channel),
																								num_channels_(num_channels)
{
	for (int i = 0; i < MAX_PPM_CHANNELS; i++)
	{
	ppm_values_[i] = 0;
	min_values_[i] = MIN_PULSE_WIDTH;
	max_values_[i] = MAX_PULSE_WIDTH;
	}

	HAL_TIM_IC_Start_IT(timer_, timer_channel_);
}

StatusCode PPMChannel::setLimits(uint8_t channel, uint32_t min, uint32_t max, uint32_t deadzone) {
	if (channel <= 0 || channel > num_channels_ || min >= max) {
		return STATUS_CODE_INVALID_ARGS;
	}

	this->min_values_[channel - 1] = min;
	this->max_values_[channel - 1] = max;

	return STATUS_CODE_OK;
}

StatusCode PPMChannel::setNumChannels(uint8_t num) {
	if (num <= 0 || num > MAX_PPM_CHANNELS) {
		return STATUS_CODE_INVALID_ARGS;
	}
	num_channels_ = num;
	return STATUS_CODE_OK;
}

uint32_t PPMChannel::getUs(uint8_t num)
{
	if(num >= num_channels_ || num >= MAX_PPM_CHANNELS) {
		return 0;
	}
	return static_cast<uint32_t>(ppm_values_[num]);
}

bool PPMChannel::isDisconnected(uint32_t sys_time) {
	// TODO: To be implemented, currently returns false only
	return CommsFailed(); // return result of RSSI Check
}

uint8_t PPMChannel::GetResult(uint8_t channel)
{
	if(channel >= num_channels_ || channel >= MAX_PPM_CHANNELS) {
		return 0;
	}

	uint8_t percentage = timeToPercentage(max_values_[channel], min_values_[channel], ppm_values_[channel]);
	return percentage;
}

float PPMChannel::counterToTime(uint32_t count, uint32_t psc)
{
	float ticksPerSecond = (BASE_FREQUENCY / (psc + 1.0f));
	float ticksPerMicroSecond = ticksPerSecond / SEC_TO_MICROSEC;

	float lengthOfPulse = count / ticksPerMicroSecond;

	return lengthOfPulse;
}


uint8_t PPMChannel::timeToPercentage(uint32_t max, uint32_t min, float time) {

	float percentage = ((time - min) / (max - min)) * 100.0f;

	if (percentage > 100.0f)
	{
		percentage = 100.0f;
	}
	else if (percentage < 0.0f)
	{
		percentage = 0.0f;
	}

	return static_cast<uint8_t>(percentage);
}

//our interrupt callback for when we get a pulse capture
void PPMChannel::interrupt_callback(TIM_HandleTypeDef * timer)
{
	if (timer->Instance == timer_->Instance)
	{
		static volatile uint8_t index = 0;

		volatile uint32_t time_diff = HAL_TIM_ReadCapturedValue(timer_, timer_channel_);
		__HAL_TIM_SET_COUNTER(timer_, 0);

		float pulseLength = counterToTime(time_diff, timer_->Init.Prescaler) - PULSE_WIDTH;

		if (pulseLength > MIN_WIDTH_OF_RESET_PULSE)
		{
			index = 0;
		}
		else if (index < MAX_PPM_CHANNELS)
		{
			ppm_values_[index] = pulseLength;
			index++;
		}
	}

}
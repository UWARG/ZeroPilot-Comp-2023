#ifndef PPM_HPP_
#define PPM_HPP_

#include <cstdint>
#include "LOS_D_RcReceiver.hpp"

enum StatusCode{STATUS_CODE_OK, STATUS_CODE_FAILED, STATUS_CODE_INVALID_ARGS};

class PPMChannel: public RcReceiver{
 public:

	PPMChannel(TIM_HandleTypeDef* timer, uint16_t timer_channel, uint8_t num_channels);

	/**
	 * Reconfigure number of channels
	 * @param num_channels
	 */
	StatusCode setNumChannels(uint8_t num_channels);

	/**
	 * Set expected input limits for a particular channel
	 * @param channel
	 * @param min Min time in us (for a 0% signal)
	 * @param max Max time in us (for 100% signal)
	 * @param deadzone time in us for deadzone. ie. if deadzone is set to 50, a signal that is received
	 * 		with a 1050us length will still be considered 0%
	 */
	StatusCode setLimits(uint8_t channel, uint32_t min, uint32_t max, uint32_t deadzone);

	/**
	 * Set the disconnect timeout
	 * @param timeout
	 * @return
	 */
	StatusCode setTimeout(uint32_t timeout);

	/**
	 * Returns a percent value that was most recently received from the PPM channel, as a percentage
	 * from 0-100
	 * @param num
	 * @return 0 if an invalid channel number was given
	 */
	uint8_t GetResult(uint8_t channel);

	/**
	 * Same as above function, but returns the captured value in microseconds instead
	 * @param num
	 * @return 0 if an invalid channel number was given
	 */
	uint32_t getUs(uint8_t num);

	/**
	 * Whether the channel has disconnected based on the timeout
	 * @param sys_time Current system time in ms
	 * @return
	 */
	bool isDisconnected(uint32_t sys_time);

 private:

	/* Constants */
	static constexpr float SEC_TO_MICROSEC 			= 1000000.0f;
	static constexpr float BASE_FREQUENCY 			= 48000000.0f;
	static constexpr float PULSE_WIDTH 				= 310.0f; // in us
	static constexpr float MIN_WIDTH_OF_RESET_PULSE = 3000.0f; // not really a pulse, this is slightly smaller than the difference in time between sequential PPM packets
	static constexpr float MIN_PULSE_WIDTH 			= 700.0f;
	static constexpr float MAX_PULSE_WIDTH			= 1670.0f;
	static constexpr uint8_t MAX_PPM_CHANNELS 		= 12;


	/* Helper Functions */
	float counterToTime(uint32_t count, uint32_t psc);
	uint8_t timeToPercentage(uint32_t max, uint32_t min, float time);

	/* Interrupt callback function */
	void interrupt_callback(TIM_HandleTypeDef * timer);

	/* Member Variables */
 	TIM_HandleTypeDef* timer_;
	uint16_t timer_channel_;
	volatile float ppm_values_[MAX_PPM_CHANNELS];
 	uint8_t num_channels_;
	float min_values_[MAX_PPM_CHANNELS]; //stores min microsecond values for each channel
	float max_values_[MAX_PPM_CHANNELS]; //stores max microsecond values for each channel
	bool is_setup_ = false;

};




#endif /* PPM_HPP_ */
#include "LOS_Link.hpp"

Los_Link& Los_Link::getInstance()
{
    static Los_Link singleton;
    return singleton;
}

Los_Link::Los_Link(){}

LosLinkRx_t Los_Link::getRx(uint8_t instance)
{
    LosLinkRx_t rx_data;

    for (uint8_t channel = 0; channel < NUM_RX_CHANNELS; channel++)
    {
        rx_data.rx_channels[channel] = rc_receivers_[instance]->GetResult(channel);
    }

    rx_data.rssi = 0; //RSSI has not been implemented so it will be set to 0

    return rx_data;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    for (uint8_t i = 0; i < NUM_RC_RECEIVER_INSTANCES; i++)
    {
        rc_receivers_[i]->interrupt_callback(htim);
    }
}
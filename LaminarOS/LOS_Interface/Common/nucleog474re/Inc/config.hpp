#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <cstdint>

/* LOS_Link */
#include "LOS_D_RcReceiver.hpp"

constexpr uint8_t NUM_RC_RECEIVER_INSTANCES = 1;
constexpr uint8_t NUM_RX_CHANNELS = 5;

extern RcReceiver* rc_receivers_[];


/* Los Actuators */
#include "LOS_D_MotorChannel.hpp"

const uint8_t NUM_ACTUATOR_CHANNELS = 2;

extern MotorChannel* motor_channels_[];

#endif // CONFIG_HPP_
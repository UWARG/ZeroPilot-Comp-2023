/*
 * SM.hpp
 *
 * System Manager Header
 *
 * Created on: Nov 7, 2022
 * Author(s): Gordon Fountain
 */

#ifndef ZPSW3_SM_HPP
#define ZPSW3_SM_HPP

#include <stdint.h>

#include "cmsis_os.h"
// #include "LOS_Link.hpp"
// #include "LOS_Actuators.hpp"
#include "AM.hpp"
#include "AM_FixedControl.hpp"
#include "SM_StateManager.hpp"
#include "interface_datatypes.hpp"

namespace SM {

/*
Constants and Enums
*/

// Enumerates the current drone status
enum Drone_Operation_Mode {
    BOOT,
    DISARMED,
    GROUND_OPS,
    TAKEOFF,
    FLIGHT,
    LANDING,
    FATAL_FAILURE = -1
};

// Enums for RSSI channel definitions
enum RC_Controller_Channel {
    RC_THROTTLE_CHANNEL,
    RC_PITCH_CHANNEL,
    RC_ROLL_CHANNEL,
    RC_YAW_CHANNEL,
    RC_ARM_CHANNEL
};  // Either reconfigure controller or this to match

/*
Helper Functions
*/

AM::AttitudeManagerInput RcToAmInput(LosLinkRx_t rc_message);

/*
System Manager
*/

class SystemState;

class SystemManager {
    public:
        SystemManager();
        void execute();
        void setState(SystemState& newState);
        Drone_Operation_Mode getMode();

        // TODO Bulk message from telemetry stored here

        // TODO Message from RC here
        LosLinkRx_t rc_data;
        // TODO new_message flag here for RC or some other way to know if data is new

        // Data from SF
        // LosSFData sf_data;

    private:
        SystemState* currentState;
        Drone_Operation_Mode operation_mode;

};

}  // namespace SM

#endif  // ZPSW3_SM_HPP

/*
 * SM_States.cpp
 *
 * System Manager State-Machine classes
 *
 * Created on: Nov 7, 2022
 * Author(s): Gordon Fountain
 */

#include "SM_States.hpp"

#include "LOS_Actuators.hpp"
#include "LOS_Link.hpp"
#include "config.hpp"
#include "cmath"
#include "task.h"
#include "LOS_Link.hpp"

namespace SM {

/********************
 * Boot Mode
 ********************/
void BootMode::execute(SystemManager *system_manager) {
    // Only Executes once, Everything startup


    // Immediately move to Disarm mode
    system_manager->setState(DisarmMode::getInstance());
}

SystemState& BootMode::getInstance() {
    static BootMode singleton;
    return singleton;
}

/********************
 * Disarm Mode
 ********************/
void DisarmMode::execute(SystemManager *system_manager) {

    // Check switch here that changes modes
    system_manager->rc_data = Los_Link::getInstance().getRx();
    if (system_manager->rc_data.rx_channels[SM::RC_ARM_CHANNEL] > 90) {
        system_manager->setState(GroundOpMode::getInstance());
    }
}

SystemState& DisarmMode::getInstance() {
    static DisarmMode singleton;
    return singleton;
}

/********************
 * Ground Op Mode
 ********************/
void GroundOpMode::execute(SystemManager *system_manager) {
    // To move to flight check that armed switch is high,
    // throttle and pitch are 0 (both sticks down)
    system_manager->rc_data = Los_Link::getInstance().getRx();
    if (system_manager->rc_data.rx_channels[SM::RC_ARM_CHANNEL] > 90 &&
        system_manager->rc_data.rx_channels[SM::RC_THROTTLE_CHANNEL] == 0 &&
        system_manager->rc_data.rx_channels[SM::RC_PITCH_CHANNEL]) {
        system_manager->setState(FlightMode::getInstance());
    }
}

void GroundOpMode::exit(SystemManager *system_manager) {

}

SystemState& GroundOpMode::getInstance() {
    static GroundOpMode singleton;
    return singleton;
}

/********************
 * Flight Mode
 ********************/
void FlightMode::enter(SystemManager *system_manager) {
}

void FlightMode::execute(SystemManager *system_manager) {

    // Get RC data from LOS
    system_manager->rc_data = Los_Link::getInstance().getRx();
    if (system_manager->rc_data.rx_channels[SM::RC_ARM_CHANNEL] < 10) {
        system_manager->setState(DisarmMode::getInstance());
    }

    // Decode RC data and convert to Mav message payload
    // dataType to_px_data = RcToPxInput(system_manager->rc_data);
    // void* msg_pointer = &to_am_data;

    // If manual control send to PX to execute
    if (system_manager->rc_data.rx_channels[SM::RC_AUTOPILOT_CHANNEL] < 10) {
        // Send message to Px

    } else {
        // If autopilot enabled then read from TM

        // Then send the message to px

    }
}

void FlightMode::exit(SystemManager *system_manager) {

    // Write 0 to LOS actuators using px
    
}

SystemState &FlightMode::getInstance() {
    static FlightMode singleton;
    return singleton;
}

/********************
 * FatalFailure Mode
 ********************/

void FatalFailureMode::enter(SystemManager *system_manager) {

    // Write 0 to LOS actuators (may need to go through px)
    for (uint8_t channel; channel < NUM_ACTUATOR_CHANNELS; channel++) {
        Los_Actuators::getInstance().set(channel, 0);
    }
}

void FatalFailureMode::execute(SystemManager *system_manager) {
    // Maybe report something? Log timstamps to SD card?
    // TBD
    system_manager->setState(FatalFailureMode::getInstance());
}

SystemState &FatalFailureMode::getInstance() {
    static FatalFailureMode singleton;
    return singleton;
}

}  // namespace SM

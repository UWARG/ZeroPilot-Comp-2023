#ifndef LOS_D_MOTOR_CHANNEL_HPP_
#define LOS_D_MOTOR_CHANNEL_HPP_

#include <cstdint>

class MotorChannel {
    public:
        virtual void setup(void) = 0;
        virtual void set(uint8_t percent) = 0;
    protected:
        bool isSetup = false;
};

#endif // LOS_D_MOTOR_CHANNEL_HPP_
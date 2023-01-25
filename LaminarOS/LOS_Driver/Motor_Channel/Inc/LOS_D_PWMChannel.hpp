#ifndef LOS_D_PWM_CHANNEL_HPP_
#define LOS_D_PWM_CHANNEL_HPP_

#include "main.h"
#include "LOS_D_MotorChannel.hpp"

class PWMChannel : public MotorChannel {
    public:
        PWMChannel(uint16_t pin_num, GPIO_TypeDef* port, 
                    TIM_HandleTypeDef* timer, uint16_t timer_channel);

        void setup(void);
        void set(uint8_t percent);
    private:
        uint16_t pin_num_;
        GPIO_TypeDef* port_;
        TIM_HandleTypeDef *timer_;     //handle to the timer
        uint16_t timer_channel_;       //channel of the timer

        uint32_t period_ticks_;

        //values in us
        static constexpr uint32_t PWM_PERIOD = 20000;
        static constexpr uint32_t MIN_SIGNAL = 950; //standard for 50hz pwm signal, with a 100 Hz margin added to ensure we can reach the extreme values.
        static constexpr uint32_t MAX_SIGNAL = 2050;

};

#endif // LOS_D_PWM_CHANNEL_HPP_
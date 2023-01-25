#ifndef RC_RECIEVER_HPP_
#define RC_RECIEVER_HPP_

#include <cstdint>
#include "main.h"

class RcReceiver{
    public:
        virtual uint8_t GetResult(uint8_t channel) = 0;
        virtual void interrupt_callback(TIM_HandleTypeDef* timer) = 0;
};

#endif
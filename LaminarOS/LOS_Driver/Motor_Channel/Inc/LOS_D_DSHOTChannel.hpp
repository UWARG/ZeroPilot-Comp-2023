#ifndef LOS_D_DSHOT_CHANNEL_HPP_
#define LOS_D_DSHOT_CHANNEL_HPP_

#include "LOS_D_PWMChannel.hpp"


class DSHOTChannel: public MotorChannel{
    public:
        DSHOTChannel(uint16_t pin_num, GPIO_TypeDef* port, TIM_HandleTypeDef* timer, 
                        uint16_t timer_channel, uint16_t tim_DMA_handle_index, 
                        uint16_t tim_dma_source);

        void setup(void);
        void set(uint8_t percent);
    private:
        static constexpr int DSHOT_DATA_FRAME_LEN = 16;

        static constexpr int DSHOT_DMA_BUFFER_SIZE    = DSHOT_DATA_FRAME_LEN + 2;
        static constexpr int DSHOT_MAX_THROTTLE       = 2000;
        static constexpr int DSHOT_RESERVED_VALUES    = 47;
        static constexpr int DSHOT_150_BIT_1          = 240;
        static constexpr int DSHOT_150_BIT_0          = 120;

        volatile uint32_t dma_buffer_[DSHOT_DMA_BUFFER_SIZE];

        uint16_t tim_dma_handle_index_;
        uint16_t tim_dma_source_;
        uint16_t pin_num_;
        GPIO_TypeDef* port_;
        TIM_HandleTypeDef *timer_;     //handle to the timer
        uint16_t timer_channel_;       //channel of the timer

        /**
        * @brief Prepares the Dshot data frame including the data, telemetry bit, and checksum
        * @param throttle_percentage Trottle percentage output from the PID loop, 0-100%
        * @param telemetry Bool indicating whether to set the telemetry bit or not
        * @retval 16 bit dshot data frame
        */    
        uint16_t prepareFrame(uint8_t throttle_percentage, bool telemetry);

        /**
        * @brief Prepares the DMA buffer using the data frame
        * @param throttle_percentage Trottle percentage output from the PID loop, 0-100%
        * @retval None
        */    
        void prepareDMABuffer(uint8_t throttle_percentage);

        /**
        * @brief Starts DMA peripheral 
        * @retval None
        */
        void startDMA();

};

#endif // LOS_D_DSHOT_CHANNEL_HPP_
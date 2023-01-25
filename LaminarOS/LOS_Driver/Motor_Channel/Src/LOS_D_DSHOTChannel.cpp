#include "LOS_D_DSHOTChannel.hpp"

DSHOTChannel::DSHOTChannel(uint16_t pin_num, GPIO_TypeDef* port, TIM_HandleTypeDef* timer, 
                            uint16_t timer_channel, uint16_t tim_DMA_handle_index, 
                            uint16_t tim_dma_source) :  pin_num_(pin_num), 
                                                        port_(port), 
                                                        timer_(timer), 
                                                        timer_channel_(timer_channel), 
                                                        tim_dma_handle_index_(tim_DMA_handle_index), 
                                                        tim_dma_source_(tim_dma_source) {}

void DSHOTChannel::setup(void) {
  HAL_TIM_PWM_Start(timer_, timer_channel_);

  //init buffer for 0 percent throttle
  prepareDMABuffer(0); 

  // Start DMA. It should never be stopped after this since it is in circular mode
  startDMA(); 

  // Enable DMA Requests
  __HAL_TIM_ENABLE_DMA(timer_, tim_dma_source_); 

  isSetup = true;
}

void DSHOTChannel::set(uint8_t percent) {
    if (percent > 100 || !isSetup) {
        return;
    }
    prepareDMABuffer(percent);
}

uint16_t DSHOTChannel::prepareFrame(uint8_t throttle_percentage, bool telemetry) {
    /* DSHOT data frame (16 bits total):
     *
     *           b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 b10 b11 b12 b13 b14 b15
     *           |-------------------------------| |-| |-------------| 
     *                      Throttle Data           ^     Checksum
     *                                              |
     *                                           Telemetry
     */
    uint16_t frame;

    frame = (((uint16_t)(DSHOT_MAX_THROTTLE * (float)throttle_percentage / 100) 
                + DSHOT_RESERVED_VALUES) << 1) | (telemetry ? 1 : 0); //throttle and telemetry bits

    //calculating checksum... splitting first 12 bits into 3 nibbles and XORing
    uint8_t checksum = (frame ^ (frame >> 4) ^ (frame >> 8)) & 0x00F; 

    frame = (frame << 4) | checksum; //adding the checksum to the frame
    
    return frame;
}

void DSHOTChannel::prepareDMABuffer(uint8_t throttle_percentage) {
    uint16_t frame = prepareFrame(throttle_percentage, false);

    for (int i = 0; i < DSHOT_DATA_FRAME_LEN; i++)
    {
        /**
         * Using the frame, populate the buffer with the duty cycle value corresponding to a 1 
         * and 0. We are masking out everything except the most significant bit (far left bit) 
         * and setting the proper value in the buffer depending if it's a 1 or 0
        */
        dma_buffer_[i] = (frame & 0x8000 ? DSHOT_150_BIT_1 : DSHOT_150_BIT_0);

        //Left shifting the current frame over by 1 to set the next frame bit in the buffer
        frame <<= 1;
    }

    //Setting the last two indexes in the buffer to 0 to ensure the last part of the signal is low
    dma_buffer_[DSHOT_DATA_FRAME_LEN] = 0;
    dma_buffer_[DSHOT_DATA_FRAME_LEN + 1] = 0;
}

void DSHOTChannel::startDMA() {
    uint32_t destination_buffer;

    switch (timer_channel_) {
        case TIM_CHANNEL_1:
            destination_buffer = (uint32_t)&timer_->Instance->CCR1;
            break;
        case TIM_CHANNEL_2:
            destination_buffer = (uint32_t)&timer_->Instance->CCR2;
            break;
        case TIM_CHANNEL_3:
            destination_buffer = (uint32_t)&timer_->Instance->CCR3;
            break;
        case TIM_CHANNEL_4:
            destination_buffer = (uint32_t)&timer_->Instance->CCR4;
            break;
    }
    HAL_DMA_Start(timer_->hdma[tim_dma_handle_index_], 
        (uint32_t)dma_buffer_, destination_buffer, DSHOT_DMA_BUFFER_SIZE);
}

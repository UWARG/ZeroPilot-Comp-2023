#ifndef LOS_ACTUATORS_HPP_
#define LOS_ACTUATORS_HPP_

#include <stdint.h>

class Los_Actuators{

    public:
        Los_Actuators(const Los_Actuators*) = delete;

        static Los_Actuators& getInstance();
        
        void set(uint8_t channel, uint8_t percent);
    
    private:
        Los_Actuators();
        
        void init(void);

};

#endif // LOS_ACTUATORS_HPP_
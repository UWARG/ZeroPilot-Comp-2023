#ifndef LOS_LINK_HPP_
#define LOS_LINK_HPP_

#include "interface_datatypes.hpp"
#include "LOS_D_RcReceiver.hpp"
#include "LOS_D_PPMChannel.hpp"

class Los_Link{

    public:
        Los_Link(const Los_Link*) = delete;

        static Los_Link& getInstance(void);
        
        LosLinkRx_t getRx(uint8_t instance = 0);

    private:
        Los_Link();
        
};

#endif
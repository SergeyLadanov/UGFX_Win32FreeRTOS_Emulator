#ifndef __UGFX_APPTIMER_HPP_
#define __UGFX_APPTIMER_HPP_


#include "gfx.h"


class UGFX_AppTimer : public GTimer
{
public:
    UGFX_AppTimer()
    {
        printf("Timer constructor\r\n");
    }


    ~UGFX_AppTimer()
    {
        printf("Timer destructor\r\n");
    }
};



#endif
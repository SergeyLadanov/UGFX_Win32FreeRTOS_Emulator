#ifndef __UGFX_GUIAPPBASE_HPP_
#define __UGFX_GUIAPPBASE_HPP_

#include <cstdio>
#include "UGFX_ScreenBase.hpp"


class UGFX_GuiAppBase
{
private:
    static constexpr uint32_t CONFIG_TASK_STACK_SIZE = 1024;
    UGFX_ScreenBase *Current = nullptr;
    GListener Gl;
    GTimer GTimer;
    uint32_t TimerTicks = 0;

public:
    void Start();
    template <typename T>
    void GoToScreen(void)
    {
        if (Current)
        {
            delete (T *) Current;
        }
        Current = new T();
    }

    void DestroyScreen()
    {
        delete Current;
        Current = nullptr;
    }

    void TimerStart(uint32_t period, uint32_t nTicks = 0xFFFFFFFF)
    {
        bool autoreload = true;
        TimerTicks = nTicks;

        auto TimerCallBack = [](void *arg)
        {
            UGFX_GuiAppBase *obj = (UGFX_GuiAppBase *) arg;
            obj->OnTimerTickCallBack();

            if (obj->TimerTicks < 0xFFFFFFFF)
            {
                if (obj->TimerTicks != 0)
                {
                    obj->TimerTicks--;

                    if (!obj->TimerTicks)
                    {
                        gtimerStop(&obj->GTimer);
                    }
                }
 
            }
        };


        if (nTicks == 0)
        {
            autoreload = false;
        }

        gtimerStart(&GTimer, TimerCallBack, this, autoreload, period);
    }


    void TimerStop()
    {
        gtimerStop(&GTimer);
    }

private:

    virtual void OnInitCallBack(void)
    {

    }

    virtual void OnTimerTickCallBack(void)
    {

    }
};

#endif
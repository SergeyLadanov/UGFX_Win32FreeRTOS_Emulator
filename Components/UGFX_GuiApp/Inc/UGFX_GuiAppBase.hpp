#ifndef __UGFX_GUIAPPBASE_HPP_
#define __UGFX_GUIAPPBASE_HPP_

#include <cstdio>
#include "UGFX_ScreenBase.hpp"
#include "UGFX_PresenterBase.hpp"


class UGFX_GuiAppBase
{
protected:
    static constexpr uint32_t CONFIG_TASK_STACK_SIZE = 1024;
    UGFX_ScreenBase *CurrentScreen = nullptr;
    UGFX_PresenterBase *CurrentPresenter = nullptr;
    GListener Gl;
    GTimer GTimer;
    uint32_t TimerTicks = 0;


    template <typename TApp, typename TScreen, typename TPresenter>
    void GoToScreen(void)
    {
        DestroyScreen();
        CurrentScreen = new TScreen();
        CurrentPresenter = new TPresenter(*(TScreen *) CurrentScreen);
        ((TScreen *) CurrentScreen)->Bind(*(TApp *) this, *(TPresenter *) CurrentPresenter);
    }

    template <typename TPresenter>
    inline TPresenter* GetCurrentPresenter()
    {
        return (TPresenter *) CurrentPresenter;
    }

    template <typename TView>
    inline TView* GetCurrentView()
    {
        return (TView *) CurrentScreen;
    }

public:
    void Start();

    void DestroyScreen()
    {
        if (CurrentScreen)
        {
            delete CurrentScreen;
            CurrentScreen = nullptr;
        }

        if (CurrentPresenter)
        {
            delete CurrentPresenter;
            CurrentPresenter = nullptr;
        }

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
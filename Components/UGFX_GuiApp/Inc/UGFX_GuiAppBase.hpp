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
    UGFX_ScreenBase *NextScreen = nullptr;
    UGFX_PresenterBase *CurrentPresenter = nullptr;
    GListener Gl;
    GTimer GTimer;
    uint32_t TimerTicks = 0;

public:
    template <typename TApp, typename TScreen, typename TPresenter>
    void GoToScreen(void)
    {
        DestroyScreen();

        CurrentScreen = new TScreen();
        if (CurrentScreen)
        {
            CurrentScreen->OnSetupScreen();
        }

        CurrentPresenter = new TPresenter(*(TScreen *) CurrentScreen);

        if (CurrentPresenter)
        {
            CurrentPresenter->Activate();
            ((TScreen *) CurrentScreen)->Bind(*(TApp *) this, *(TPresenter *) CurrentPresenter);
        }
        
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


    void Start();

    void DestroyScreen();

    void TimerStart(uint32_t period, uint32_t nTicks = 0xFFFFFFFF);

    void TimerStop();

private:

    virtual void OnInitCallBack(void)
    {

    }

    virtual void OnTimerTickCallBack(void)
    {

    }
};

#endif
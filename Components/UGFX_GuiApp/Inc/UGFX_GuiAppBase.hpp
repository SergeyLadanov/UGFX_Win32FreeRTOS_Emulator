#ifndef __UGFX_GUIAPPBASE_HPP_
#define __UGFX_GUIAPPBASE_HPP_

#include <cstdio>
#include "UGFX_ScreenBase.hpp"
#include "UGFX_PresenterBase.hpp"
#include "UGFX_AppTimer.hpp"


class UGFX_GuiAppBase
{
protected:
    static constexpr uint32_t CONFIG_TASK_STACK_SIZE = 512;
    UGFX_ScreenBase *CurrentScreen = nullptr;
    UGFX_ScreenBase *NextScreen = nullptr;
    UGFX_PresenterBase *CurrentPresenter = nullptr;
    UGFX_PresenterBase *NextPresenter = nullptr;
    GListener Gl;
    GTimer Gtimer;
    uint32_t TimerTicks = 0;


    int16_t AnimationOffset = 0;

public:

    template <typename TApp, typename TScreen, typename TPresenter>
    void GoToScreen(void)
    {
        DestroyScreen();

        CurrentScreen = new TScreen();
        if (CurrentScreen)
        {
            CurrentScreen->OnSetupScreen();
            CurrentScreen->Show();
        }

        

        CurrentPresenter = new TPresenter(*(TScreen *) CurrentScreen);

        if (CurrentPresenter)
        {
            CurrentPresenter->Activate();
            ((TScreen *) CurrentScreen)->Bind(*(TApp *) this, *(TPresenter *) CurrentPresenter);
        }
        
    }

    template <typename TApp, typename TScreen, typename TPresenter>
    void GoToScreenAnimation(void)
    {
        NextScreen = new TScreen();
        if (NextScreen)
        {
            NextScreen->SetPos(0, -gdispGetHeight());
            NextScreen->Show();
        }

        NextPresenter = new TPresenter(*(TScreen *) CurrentScreen);

        TimerStart(25, gdispGetHeight()/20);
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
#ifndef __UGFX_GUIAPPBASE_HPP_
#define __UGFX_GUIAPPBASE_HPP_

#include <cstdio>
#include "UGFX_ScreenBase.hpp"
#include "UGFX_PresenterBase.hpp"
#include "UGFX_AppTimer.hpp"


class UGFX_GuiAppBase
{
protected:
    UGFX_ScreenBase *CurrentScreen = nullptr;
    UGFX_PresenterBase *CurrentPresenter = nullptr;
    GListener Gl;
    bool ScreenReady = false;
public:

    template <typename TApp, typename TScreen, typename TPresenter>
    void GoToScreen(void)
    {
        DestroyScreen();

        CurrentScreen = new TScreen();
        if (CurrentScreen)
        {
            CurrentScreen->OnSetupScreen();

            CurrentPresenter = new TPresenter(*(TScreen *) CurrentScreen);

            if (CurrentPresenter)
            {
                ((TScreen *) CurrentScreen)->Bind(*(TApp *) this, *(TPresenter *) CurrentPresenter);
                CurrentPresenter->Activate();
            }

            CurrentScreen->Show();

            ScreenReady = true;
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

    void Start(uint32_t task_stack = 512);

    void DestroyScreen();

protected:

    virtual void OnInitCallBack(void)
    {

    }
};

#endif
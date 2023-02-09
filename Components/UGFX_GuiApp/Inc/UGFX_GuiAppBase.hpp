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
    UGFX_PresenterBase *CurrentPresenter = nullptr;
    GListener Gl;
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

protected:

    virtual void OnInitCallBack(void)
    {

    }
};

#endif
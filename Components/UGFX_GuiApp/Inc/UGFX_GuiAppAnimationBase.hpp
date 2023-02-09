#ifndef __UGFX_GUIAPPANIMATIONBASE_HPP_
#define __UGFX_GUIAPPANIMATIONBASE_HPP_

#include "UGFX_GuiAppBase.hpp"

class UGFX_GuiAppAnimationBase : public UGFX_GuiAppBase
{
protected:
    UGFX_PresenterBase *NextPresenter = nullptr;
    UGFX_ScreenBase *NextScreen = nullptr;
    UGFX_AppTimer Timer;

public:
    // template <typename TApp, typename TScreen, typename TPresenter>
    // void GoToScreenAnimation(void)
    // {
    //     NextScreen = new TScreen();
    //     if (NextScreen)
    //     {
    //         NextScreen->SetPos(0, -gdispGetHeight());
    //         NextScreen->Show();
    //     }

    //     NextPresenter = new TPresenter(*(TScreen *) CurrentScreen);

    //     TimerStart(25, gdispGetHeight()/20);
    // }
};

#endif
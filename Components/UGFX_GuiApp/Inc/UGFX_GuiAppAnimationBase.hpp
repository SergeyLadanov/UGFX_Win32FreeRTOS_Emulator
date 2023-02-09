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

    UGFX_GuiAppAnimationBase()
    {
        auto AnimationTick = [](void *arg)
        {
            UGFX_GuiAppAnimationBase *obj = (UGFX_GuiAppAnimationBase *) arg;
            printf("Animation timer tick...\r\n");

            if (obj->NextScreen)
            {
                obj->NextScreen->MoveOn(0, 20);
                obj->CurrentScreen->MoveOn(0, 20);
            }
        };


        auto AnimationEnd = [](void *arg)
        {
            UGFX_GuiAppAnimationBase *obj = (UGFX_GuiAppAnimationBase *) arg;
            printf("Animation timer stopped...\r\n");

            obj->DestroyScreen();

            obj->CurrentPresenter = obj->NextPresenter;
            obj->NextPresenter = nullptr;

            obj->CurrentScreen = obj->NextScreen;
            obj->NextScreen = nullptr;

            obj->CurrentScreen->SetPos(0, 0);
        };

        Timer.SetArg(this);
        Timer.SetTickCallBack(AnimationTick);
        Timer.SetEndCallBack(AnimationEnd);
    }


    template <typename TApp, typename TScreen, typename TPresenter>
    void GoToScreenAnimation(void)
    {
        NextScreen = new TScreen();

        if (NextScreen)
        {
            NextScreen->SetPos(0, -gdispGetHeight());
            NextScreen->OnSetupScreen();

            NextPresenter = new TPresenter(*(TScreen *) NextScreen);
            if (NextPresenter)
            {
                ((TScreen *) NextScreen)->Bind(*(TApp *) this, *(TPresenter *) NextPresenter);
                NextPresenter->Activate();
            }
            NextScreen->Show();
            Timer.Start(25, gdispGetHeight()/20);
        }
    }


    template <typename TPresenter>
    inline TPresenter* GetNextPresenter()
    {
        return (TPresenter *) NextPresenter;
    }

    template <typename TView>
    inline TView* GetNextView()
    {
        return (TView *) NextScreen;
    }
};

#endif
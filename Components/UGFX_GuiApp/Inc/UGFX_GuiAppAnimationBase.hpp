#ifndef __UGFX_GUIAPPANIMATIONBASE_HPP_
#define __UGFX_GUIAPPANIMATIONBASE_HPP_

#include "UGFX_GuiAppBase.hpp"

class UGFX_GuiAppAnimationBase : public UGFX_GuiAppBase
{
public:
    typedef enum
    {
        ANIMATION_UP_TO_DOWN = 0,
        ANIMATION_DOWN_TO_UP,
        ANIMATION_LEFT_TO_RIGHT,
        ANIMATION_RIGHT_TO_LEFT,
    } AinmatoinType;

protected:
    UGFX_PresenterBase *NextPresenter = nullptr;
    UGFX_ScreenBase *NextScreen = nullptr;
    UGFX_AppTimer Timer;
    int16_t X_Step = 0;
    int16_t Y_Step = 0;
    uint32_t TransactionPeriod = 0;
    uint32_t TransactionStepNumber = 0;
public:

    UGFX_GuiAppAnimationBase()
    {
        auto AnimationTick = [](void *arg)
        {
            UGFX_GuiAppAnimationBase *obj = (UGFX_GuiAppAnimationBase *) arg;
            // printf("Animation timer tick...\r\n");

            if (obj->NextScreen)
            {
                obj->NextScreen->MoveOn(obj->X_Step, obj->Y_Step);
                obj->CurrentScreen->MoveOn(obj->X_Step, obj->Y_Step);
            }
        };


        auto AnimationEnd = [](void *arg)
        {
            UGFX_GuiAppAnimationBase *obj = (UGFX_GuiAppAnimationBase *) arg;
            // printf("Animation timer stopped...\r\n");

            obj->DestroyScreen();

            obj->CurrentPresenter = obj->NextPresenter;
            obj->NextPresenter = nullptr;

            obj->CurrentScreen = obj->NextScreen;
            obj->NextScreen = nullptr;

            obj->CurrentScreen->SetPos(0, 0);

            obj->ScreenReady = true;
        };

        Timer.SetArg(this);
        Timer.SetTickCallBack(AnimationTick);
        Timer.SetEndCallBack(AnimationEnd);
    }


    template <typename TApp, typename TScreen, typename TPresenter>
    void GoToScreenAnimation(uint16_t step, uint32_t period, AinmatoinType animationType = ANIMATION_UP_TO_DOWN)
    {
        NextScreen = new TScreen();

        ScreenReady = false;

        int16_t StartPosY = 0;
        int16_t StartPosX = 0;
        uint32_t Length = 0;

        switch(animationType)
        {
            case ANIMATION_UP_TO_DOWN :
                StartPosY = -gdispGetHeight();
                Length = gdispGetHeight();
                X_Step = 0;
                Y_Step = ((int16_t) step);
            break;

            case ANIMATION_DOWN_TO_UP :
                StartPosY = gdispGetHeight();
                Length = gdispGetHeight();
                X_Step = 0;
                Y_Step = -((int16_t) step);
            break;

            case ANIMATION_LEFT_TO_RIGHT :
                StartPosX = -gdispGetWidth();
                Length = gdispGetWidth();
                X_Step = ((int16_t) step);
                Y_Step = 0;
            break;

            case ANIMATION_RIGHT_TO_LEFT :
                StartPosX = gdispGetWidth();
                Length = gdispGetWidth();
                X_Step = -((int16_t) step);
                Y_Step = 0;

            break;

            default :

            break;
        };



        if (NextScreen)
        {
            NextScreen->SetPos(StartPosX, StartPosY);
            
            NextPresenter = new TPresenter(*(TScreen *) NextScreen);
            if (NextPresenter)
            {
                ((TScreen *) NextScreen)->Bind(*(TApp *) this, *(TPresenter *) NextPresenter);
                
            }
            
            TransactionPeriod = period;
            TransactionStepNumber = Length/step;
        }
    }


    void EndScreenAnimationTransaction(void)
    {
        NextScreen->OnSetupScreen();

        NextPresenter->Activate();

        NextScreen->Show();

        Timer.Start(TransactionPeriod, TransactionStepNumber);
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
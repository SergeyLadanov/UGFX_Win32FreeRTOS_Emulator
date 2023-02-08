#ifndef __GUI_APP_HPP_
#define __GUI_APP_HPP_

#include "UGFX_GuiAppBase.hpp"

#include "Model.hpp"

class GUI_App : public UGFX_GuiAppBase
{
private:
    Model &ModelRef;

    void OnInitCallBack(void) override;

    void OnTimerTickCallBack(void) override;
public:
    GUI_App(Model &model)
        : ModelRef(model)
    {

    }


    template <typename TScreen, typename TPresenter>
    void GoToScreen(void)
    {
        UGFX_GuiAppBase::GoToScreen<typeof(*this), TScreen, TPresenter>();
        GetCurrentPresenter<TPresenter>()->BindModel(&ModelRef);
    }


    template <typename TScreen, typename TPresenter>
    void GoToScreenAnimation(void)
    {
        UGFX_GuiAppBase::GoToScreenAnimation<typeof(*this), TScreen, TPresenter>();
    }
    
    void GoToMainScreen(void);
    void GoToScreen2(void);
    void GoToScreen2Animation(void);
};



#endif
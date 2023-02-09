#ifndef __GUI_APP_HPP_
#define __GUI_APP_HPP_

#include "UGFX_GuiAppAnimationBase.hpp"

#include "Model.hpp"

class GUI_App : public UGFX_GuiAppAnimationBase
{
private:
    Model &ModelRef;

    void OnInitCallBack(void) override;

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
    
    void GoToMainScreen(void);
    void GoToScreen2(void);
};



#endif
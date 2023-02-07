#ifndef __GUI_APP_HPP_
#define __GUI_APP_HPP_

#include "UGFX_GuiAppBase.hpp"


class GUI_App : public UGFX_GuiAppBase
{
private:
    void OnInitCallBack(void) override
    {
        TimerStart(500);
    }

    void OnTimerTickCallBack(void) override;
public:
    void GoToMainScreen(void);

};



#endif
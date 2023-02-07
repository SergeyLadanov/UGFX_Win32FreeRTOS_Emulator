#ifndef __GUIAPP_HPP_
#define __GUIAPP_HPP_

#include "UGFX_GuiAppBase.hpp"
#include "MainScreen.hpp"


class GUI_App : public UGFX_GuiAppBase
{
private:
    void OnInitCallBack(void) override
    {
        TimerStart(2000, 6);
    }

    void OnTimerTickCallBack(void) override
    {
        static bool direction = false;

        if (!direction)
        {
            GoToScreen<MainScreen>();
        }
        else
        {
            DestroyScreen();
        }

        direction = !direction;
    }
};



#endif
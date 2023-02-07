#include "GUI_App.hpp"
#include "MainScreen.hpp"


void GUI_App::GoToMainScreen(void)
{
    GoToScreen<GUI_App, MainScreen, MainPresenter>();
    
}


void GUI_App::OnTimerTickCallBack(void)
{
    static bool direction = false;

    if (!direction)
    {
        GoToMainScreen();
    }
    else
    {
        DestroyScreen();
    }

    direction = !direction;
}
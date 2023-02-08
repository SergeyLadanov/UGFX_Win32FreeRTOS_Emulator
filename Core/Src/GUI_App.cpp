#include "GUI_App.hpp"
#include "MainScreen.hpp"


void GUI_App::OnInitCallBack(void)
{
    TimerStart(500);
    GoToMainScreen();
}


void GUI_App::GoToMainScreen(void)
{
    GoToScreen<MainScreen, MainPresenter>();
}


void GUI_App::OnTimerTickCallBack(void)
{
    ModelRef.Tick();
    //CurrentScreen->MoveOn(-2, -2);

    // static bool direction = false;

    // if (!direction)
    // {
    //     GoToMainScreen();
    // }
    // else
    // {
    //     DestroyScreen();
    // }

    // direction = !direction;
}
#include "GUI_App.hpp"
#include "MainScreen.hpp"
#include "Screen2.hpp"


void GUI_App::OnInitCallBack(void)
{
    GoToMainScreen();
}

void GUI_App::GoToScreen2(void)
{
    GoToScreen<Screen2, Screen2Presenter>();
}

void GUI_App::GoToScreen2Animation(void)
{
    GoToScreenAnimation<Screen2, Screen2Presenter>();
}

void GUI_App::GoToMainScreen(void)
{
    GoToScreen<MainScreen, MainPresenter>();
}

 void GUI_App::GoToMainScreenAnimation(void)
 {
    GoToScreenAnimation<MainScreen, MainPresenter>();
 }

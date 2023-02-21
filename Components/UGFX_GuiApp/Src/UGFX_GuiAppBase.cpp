#include "UGFX_GuiAppBase.hpp"



gThreadreturn UGFX_GuiAppBase::GuiTask(void *arg)
{
    UGFX_GuiAppBase* obj = (UGFX_GuiAppBase *) arg;
    GEvent* pe;

    gfxInit();
    geventListenerInit(&obj->Gl);
    gwinAttachListener(&obj->Gl);
    obj->OnInitCallBack();

    for(;;)
    {
        pe = geventEventWait(&obj->Gl, TIME_INFINITE);
        if (obj->CurrentScreen)
        {
            if (obj->ScreenReady)
            {
                obj->CurrentScreen->HandleUgfxEvent(pe);
            }  
        }

        obj->HandleUgfxEvent(pe);
    }

    gfxThreadReturn(0);
}


void UGFX_GuiAppBase::Start(uint32_t task_stack)
{
    gfxThreadCreate(nullptr, task_stack, gThreadpriorityLow, GuiTask, this);
}


void UGFX_GuiAppBase::DestroyScreen()
{
    ScreenReady = false;
    if (CurrentPresenter)
    {
        CurrentPresenter->DeActivate();
        delete CurrentPresenter;
        CurrentPresenter = nullptr;
    }

    if (CurrentScreen)
    {
        CurrentScreen->OnExitScreen();
        delete CurrentScreen;
        CurrentScreen = nullptr;
    }
}


void UGFX_GuiAppBase::EndScreenTransaction(void)
{
    CurrentScreen->OnSetupScreen();

    CurrentPresenter->Activate();

    CurrentScreen->Show();

    ScreenReady = true;
}


void UGFX_GuiAppBase::OnInitCallBack(void)
{

}


void UGFX_GuiAppBase::HandleUgfxEvent(GEvent* pe)
{

}
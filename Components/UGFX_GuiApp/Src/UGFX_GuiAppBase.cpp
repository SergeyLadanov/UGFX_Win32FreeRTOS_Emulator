#include "UGFX_GuiAppBase.hpp"


void UGFX_GuiAppBase::Start()
{
    auto GuiTask = [](void *arg)
    {
        UGFX_GuiAppBase* obj = (UGFX_GuiAppBase *) arg;
        GEvent* pe;

        gfxInit();
        gdispClear(Black);
        gwinSetDefaultFont(gdispOpenFont("UI2"));

        geventListenerInit(&obj->Gl);
        gwinAttachListener(&obj->Gl);
        geventAttachSource(&obj->Gl, ginputGetKeyboard(GKEYBOARD_ALL_INSTANCES), 0);

        obj->OnInitCallBack();

        for(;;)
        {
            pe = geventEventWait(&obj->Gl, TIME_INFINITE);
            printf("Event processed!\r\n");
            if (obj->CurrentScreen)
            {
                obj->CurrentScreen->HandleUgfxEvent(pe);
            }
        }
    };

    // GuiTask(this);

    gfxThreadCreate(nullptr, CONFIG_TASK_STACK_SIZE, gThreadpriorityLow, GuiTask, this);
}




void UGFX_GuiAppBase::DestroyScreen()
{

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
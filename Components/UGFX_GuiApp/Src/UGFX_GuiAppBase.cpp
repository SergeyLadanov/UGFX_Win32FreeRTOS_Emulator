#include "UGFX_GuiAppBase.hpp"


void UGFX_GuiAppBase::Start(uint32_t task_stack)
{
    
    auto GuiTask = [](void *arg)->gThreadreturn
    {
        UGFX_GuiAppBase* obj = (UGFX_GuiAppBase *) arg;
        GEvent* pe;

        gfxInit();
        geventListenerInit(&obj->Gl);
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
    };

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
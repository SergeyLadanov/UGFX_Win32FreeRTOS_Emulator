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

void UGFX_GuiAppBase::TimerStart(uint32_t period, uint32_t nTicks)
{
    bool autoreload = true;
    TimerTicks = nTicks;

    auto TimerCallBack = [](void *arg)
    {
        UGFX_GuiAppBase *obj = (UGFX_GuiAppBase *) arg;
        obj->OnTimerTickCallBack();

        if (obj->CurrentScreen)
        {
            obj->CurrentScreen->OnTimeTickCallBack();
        }
        

        if (obj->TimerTicks < 0xFFFFFFFF)
        {
            if (obj->TimerTicks != 0)
            {
                obj->TimerTicks--;

                if (!obj->TimerTicks)
                {
                    gtimerStop(&obj->GTimer);
                }
            }

        }
    };


    if (nTicks == 0)
    {
        autoreload = false;
    }

    gtimerStart(&GTimer, TimerCallBack, this, autoreload, period);
}


void UGFX_GuiAppBase::TimerStop()
{
    gtimerStop(&GTimer);
}
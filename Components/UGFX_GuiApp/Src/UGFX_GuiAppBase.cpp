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

    GuiTask(this);

    //gfxThreadCreate(nullptr, CONFIG_TASK_STACK_SIZE, gThreadpriorityLow, GuiTask, this);
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

    if (gtimerIsActive(&Gtimer))
    {
        TimerStop();
    }

    auto TimerCallBack = [](void *arg)
    {
        UGFX_GuiAppBase *obj = (UGFX_GuiAppBase *) arg;
        obj->OnTimerTickCallBack();


        if (obj->NextScreen)
        {
            if (obj->CurrentScreen)
            {
                
                obj->CurrentScreen->MoveOn(0, 1);
                
                // gdispGetHeight();
                // gdispGetWidth();
            }

            obj->NextScreen->MoveOn(0, 1);

            if (obj->AnimationOffset > 0)
            {
                obj->AnimationOffset--;
            }

            if (obj->AnimationOffset < 0)
            {
                obj->AnimationOffset++;
            }
        }
        else
        {
            if (obj->CurrentScreen)
            {
                obj->CurrentScreen->OnTimeTickCallBack();
            }
        }
            

        if (obj->TimerTicks < 0xFFFFFFFF)
        {
            if (obj->TimerTicks != 0)
            {
                obj->TimerTicks--;

                if (!obj->TimerTicks)
                {
                    gtimerStop(&obj->Gtimer);
                }
            }

        }
        



    };


    if (nTicks == 0)
    {
        autoreload = false;
    }

    gtimerStart(&Gtimer, TimerCallBack, this, autoreload, period);
}


void UGFX_GuiAppBase::TimerStop()
{
    gtimerStop(&Gtimer);
}
#include "UGFX_GuiAppBase.hpp"


void UGFX_GuiAppBase::Start()
{
	geventListenerInit(&Gl);
	gwinAttachListener(&Gl);
	geventAttachSource(&Gl, ginputGetKeyboard(GKEYBOARD_ALL_INSTANCES), 0);


    auto GuiTask = [](void *arg)
    {
        UGFX_GuiAppBase* obj = (UGFX_GuiAppBase *) arg;
        GEvent* pe;

        for(;;)
        {
            pe = geventEventWait(&obj->Gl, TIME_INFINITE);
            printf("Event processed!\r\n");
            if (obj->Current)
            {
                obj->Current->HandleUgfxEvent(pe);
            }
        }
    };

    xTaskCreate(GuiTask, "Ugfx", configMINIMAL_STACK_SIZE * 4, this, 0, NULL);
}
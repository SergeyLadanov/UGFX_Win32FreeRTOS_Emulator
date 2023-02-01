#include "gfx.h"
#include <stdio.h>


static GListener gl;
static GHandle   ghButton1;
static GHandle      ghContainer;

static uint8_t key = 0;

static GEvent* pe;

static void createWidgets(void) {
	GWidgetInit	wi;

	// Apply some default values for GWIN
	gwinWidgetClearInit(&wi);



    // Apply the container parameters
    // wi.g.show = FALSE;
    // wi.g.width = 128;
    // wi.g.height = 64;
    // wi.g.y = 0;
    // wi.g.x = 0;
    // wi.text = "Container";
    // ghContainer = gwinContainerCreate(0, &wi, GWIN_CONTAINER_BORDER);


	wi.g.show = TRUE;

	// Apply the button parameters
	wi.g.width = 100;
	wi.g.height = 30;
	wi.g.y = 10;
	wi.g.x = 10;
	wi.text = "Test";
	wi.g.parent = NULL;

	// Create the actual button
	ghButton1 = gwinButtonCreate(0, &wi);

	//gwinShow(ghContainer);

}



int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;
	
	gfxInit();
	gdispClear(Silver);

	

	createWidgets();

	geventListenerInit(&gl);
	gwinAttachListener(&gl);
	geventAttachSource(&gl, ginputGetKeyboard(0), 0);
	

	
	// gdispSetClip(70,70,100,100);
	// gdispFillArea(-10, -10, 100, 100, Black);
	
	while (1) {
		gfxSleepMilliseconds(10);
		pe = geventEventWait(&gl, TIME_INFINITE);

		switch(pe->type) {
			case GEVENT_KEYBOARD:
				printf("Keyboard\r\n");

				key = ((GEventKeyboard *) pe)->c[0];
				if (key == GKEY_UP)
				{
					printf("Up\r\n");
				}

				if (key == GKEY_DOWN)
				{
					printf("Down\r\n");
				}
				
				break;
			case GEVENT_GWIN_BUTTON:
			
				printf("Gwin button pressed\r\n");
				break;

			default:
				break;
		}
		
	}

	return 0;
}

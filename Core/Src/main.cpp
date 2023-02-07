/*
 * FreeRTOS V202212.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/******************************************************************************
 * This project provides two demo applications.  A simple blinky style project,
 * and a more comprehensive test and demo application.  The
 * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting is used to select between the two.
 * The simply blinky demo is implemented and described in main_blinky.c.  The
 * more comprehensive test and demo application is implemented and described in
 * main_full.c.
 *
 * This file implements the code that is not demo specific, including the
 * hardware setup and FreeRTOS hook functions.
 *
 *******************************************************************************
 * NOTE: Windows will not be running the FreeRTOS demo threads continuously, so
 * do not expect to get real time behaviour from the FreeRTOS Windows port, or
 * this demo application.  Also, the timing information in the FreeRTOS+Trace
 * logs have no meaningful units.  See the documentation page for the Windows
 * port for further information:
 * https://www.FreeRTOS.org/FreeRTOS-Windows-Simulator-Emulator-for-Visual-Studio-and-Eclipse-MingW.html
 *

 *
 *******************************************************************************
 */

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "gfx.h"
#include "MainScreen.hpp"
#include "UGFX_GuiAppBase.hpp"



extern void  prvInitialiseHeap( void );

static GListener gl;
static GHandle   ghButton1;
static GHandle      ghContainer, image1, image2;
static uint8_t key = 0;
static GEvent* pe;

GTimer GT1;

UGFX_ScreenBase *test;
UGFX_GuiAppBase AppTest;




static void createWidgets(void) {

	test = new MainScreen();
	// GWidgetInit	wi;

	// // Apply some default values for GWIN
	// gwinWidgetClearInit(&wi);


    // // Apply the container parameters
    // // wi.g.show = FALSE;
    // // wi.g.width = 128;
    // // wi.g.height = 64;
    // // wi.g.y = 0;
    // // wi.g.x = 0;
    // // wi.text = "Container";
    // // ghContainer = gwinContainerCreate(0, &wi, GWIN_CONTAINER_BORDER);


	// wi.g.show = TRUE;

	// // Apply the button parameters
	// wi.g.width = 100;
	// wi.g.height = 30;
	// wi.g.y = 10;
	// wi.g.x = 10;
	// wi.text = "Test";
	// wi.g.parent = NULL;

	// // Create the actual button
	// ghButton1 = gwinButtonCreate(0, &wi);


	// wi.g.show = false;

	// // Apply the button parameters
	// wi.g.width = 32;
	// wi.g.height = 32;
	// wi.g.y = 50;
	// wi.g.x = 50;

	// image1 = gwinImageCreate(0, &wi.g);
	// gwinImageOpenFile(image1, "menu_display.png");
	// gwinShow(image1);


	// wi.g.show = false;
	// // Apply the button parameters
	// wi.g.width = 32;
	// wi.g.height = 32;
	// wi.g.y = 40;
	// wi.g.x = 40;

	// image2 = gwinImageCreate(0, &wi.g);
	// gwinImageOpenFile(image2, "menu_display.png");
	// gwinShow(image2);

}


static void TaskTest(void *arg)
{
    for(;;)
    {
        printf("Test\r\n");
        vTaskDelay(1000);
    }
}

static void callback1(void* arg)
{
    (void)arg;
	static bool direction = false;

	if (!direction)
	{
		AppTest.GoToScreen<MainScreen>();
	}
	else
	{
		AppTest.DestroyScreen();
	}

	direction = !direction;
}


static void UgfxTask(void *pvParameters)
{
	GEvent* pe;

	gfxInit();
	gdispClear(Black);
	gwinSetDefaultFont(gdispOpenFont("UI2"));
	

	//createWidgets();
	AppTest.Start();
	/* continious mode - callback1() called without any argument every 250ms */
    gtimerStart(&GT1, callback1, NULL, TRUE, 2000);

	for(;;) 
	{
		vTaskDelay(100);
	}
}



/*-----------------------------------------------------------*/

int main( void )
{
	prvInitialiseHeap();

	xTaskCreate(TaskTest, "Test", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 3, NULL);
	xTaskCreate(UgfxTask, "Ugfx", configMINIMAL_STACK_SIZE * 4, NULL, 0, NULL);

	vTaskStartScheduler();

	for(;;)
	{

	}

	return 0;
}
/*-----------------------------------------------------------*/









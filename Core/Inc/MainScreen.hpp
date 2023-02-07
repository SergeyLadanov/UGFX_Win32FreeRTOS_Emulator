#ifndef __MAINSCREEN_HPP_
#define __MAINSCREEN_HPP_

#include "UGFX_ScreenBase.hpp"


class MainScreen : public UGFX_ScreenBase
{
private:
    GHandle ghButton1;
    GHandle image1, image2;
public:
    MainScreen()
    {

        Widget.g.show = true;

        // Apply the button parameters
        Widget.g.width = 100;
        Widget.g.height = 30;
        Widget.g.y = 10;
        Widget.g.x = 10;
        Widget.text = "Test";

        // Create the actual button
        ghButton1 = gwinButtonCreate(0, &Widget);


        Widget.g.show = true;

        // Apply the button parameters
        Widget.g.width = 32;
        Widget.g.height = 32;
        Widget.g.y = 50;
        Widget.g.x = 50;

        image1 = gwinImageCreate(0, &Widget.g);
        gwinImageOpenFile(image1, "menu_display.png");
        gwinShow(image1);


        Widget.g.show = true;
        // Apply the button parameters
        Widget.g.width = 32;
        Widget.g.height = 32;
        Widget.g.y = 40;
        Widget.g.x = 40;

        image2 = gwinImageCreate(0, &Widget.g);
        gwinImageOpenFile(image2, "menu_display.png");
        gwinShow(image2);
        gwinShow(Container);
    }
};



#endif
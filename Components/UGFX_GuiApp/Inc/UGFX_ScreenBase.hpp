#ifndef __UGFX_SCREENBASE_HPP_
#define __UGFX_SCREENBASE_HPP_

#include <cstdio>
#include "gfx.h"



class UGFX_ScreenBase
{
protected:
    GHandle Container;
    GWidgetInit	Widget;
public:
    UGFX_ScreenBase(void)
    {
        gwinWidgetClearInit(&Widget);
        Widget.g.show = FALSE;
        Widget.g.width = gdispGetWidth();
        Widget.g.height = gdispGetHeight();
        Widget.g.y = 0;
        Widget.g.x = 0;
        Widget.text = "";
        Container = gwinContainerCreate(0, &Widget, 0);
        Widget.g.parent = Container;
    }

    virtual void HandleUgfxEvent(GEvent* pe)
    {

    }

    ~UGFX_ScreenBase()
    {
        GHandle	child;

        for(child = gwinGetFirstChild(Container); child; child = gwinGetFirstChild(Container))
        {
            gwinDestroy(child);
        }

        gwinDestroy(Container);
    }

};


#endif
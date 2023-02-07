#ifndef __UGFX_GUIAPPBASE_HPP_
#define __UGFX_GUIAPPBASE_HPP_

#include <cstdio>
#include "UGFX_ScreenBase.hpp"


class UGFX_GuiAppBase
{
private:
    UGFX_ScreenBase *Current = nullptr;
    GListener Gl;

public:
    void Start();
    template <typename T>
    void GoToScreen(void)
    {
        if (Current)
        {
            delete (T *) Current;
        }
        Current = new T();
    }

    void DestroyScreen()
    {
        delete Current;
        Current = nullptr;
    }
};

#endif
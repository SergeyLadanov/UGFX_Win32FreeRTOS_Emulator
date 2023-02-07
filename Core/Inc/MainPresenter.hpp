#ifndef __MAINPRESENTER_HPP_
#define __MAINPRESENTER_HPP_

#include "UGFX_PresenterBase.hpp"


class MainScreen;

class MainPresenter : public UGFX_PresenterBase
{
protected:
    MainScreen &View;
public:
    MainPresenter(MainScreen &view)
        :View(view)
    {

    }
};


#endif
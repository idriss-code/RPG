#include "Continue.h"


Continue::Continue(const char* name):ElementMenu(name)
{
    //ctor


}

Continue::~Continue()
{
    //dtor
}

int Continue::action(int val)
{
    return PLAY;
}


#include "MultiSwitch.h"

MultiSwitch::MultiSwitch(bool ActionOnEnter): actionOnEnter(ActionOnEnter) , nbElement(0)
{
    //ctor
}

MultiSwitch::~MultiSwitch()
{
    //dtor
}

int MultiSwitch::action()
{
    int returnVal=0;
    for(int i=0;i<nbElement;i++){
        returnVal=tab[i]->action();
    }
    return returnVal;
}

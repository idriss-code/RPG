#ifndef MULTISWITCH_H
#define MULTISWITCH_H

#include "MapElement.h"

class MultiSwitch : public MapElement
{
    public:
        MultiSwitch(bool ActionOnEnter=false);

        virtual ~MultiSwitch();

        virtual bool isAWall() const {return false;}
        virtual bool doActionOnEnter() const {return actionOnEnter;}
        virtual bool doActionOnAction() const {return !actionOnEnter;}
        virtual bool isACombatZone() const {return false;}

        virtual int action();

        void addElement(MapElement* val){tab[nbElement++]=val;}

    protected:

    private:
        bool actionOnEnter;
        MapElement* tab[100];
        int nbElement;
};

#endif // MULTISWITCH_H

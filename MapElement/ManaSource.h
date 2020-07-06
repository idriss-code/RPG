#ifndef MANASOURCE_H
#define MANASOURCE_H

#include "MapElement.h"

class Group;

class ManaSource : public MapElement
{
    public:
        ManaSource();
        virtual ~ManaSource();

        virtual bool isAWall() const {return false;}
        virtual bool doActionOnEnter() const {return true;}
        virtual bool doActionOnAction() const {return false;}
        virtual bool isACombatZone() const {return false;}
        virtual void reset(){actived=false;};

        virtual int action();

    protected:

    private:
        bool actived;

};

#endif // MANASOURCE_H

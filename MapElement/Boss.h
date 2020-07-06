#ifndef BOSS_H
#define BOSS_H

#include "MapElement.h"

class Group;

class Boss : public MapElement
{
    public:
        Boss(Group* boss);
        virtual ~Boss();

        virtual bool isAWall() const {return false;}
        virtual bool doActionOnEnter() const {return true;}
        virtual bool doActionOnAction() const {return false;}
        virtual bool isACombatZone() const {return false;}

        virtual int action();

    protected:

    private:
        Group* theBoss;
        bool isAlive;

};

#endif // BOSS_H

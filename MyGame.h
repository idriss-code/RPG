#ifndef MYGAME_H
#define MYGAME_H

#include "core/Game.h"
#include "Map/FinalMap.h"


class MyGame : public Game
{
    public:
        MyGame();
        virtual ~MyGame();

    protected:

    private:
        void initHero();
        FinalMap* initMap;

};

#endif // MYGAME_H

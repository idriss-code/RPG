#ifndef MYGAME_H
#define MYGAME_H

#include "Game.h"

#include "Map/FinalMap.h"

class MyGame : public Game
{
    public:
        MyGame();
        virtual ~MyGame();
        void main();

    protected:

    private:
        void initHero();
        FinalMap* initMap;
};

#endif // MYGAME_H

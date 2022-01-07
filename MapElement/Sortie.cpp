#include "Sortie.h"
#include "../constante.h"

#include "../Player.h"
#include "../core/Game.h"
#include "../Map/FinalMap.h"


extern Player player;

extern Game* game;

Sortie::Sortie(FinalMap* destination,int x,int y):m_x(x),m_y(y),m_destination(destination)
{
    //ctor
}

Sortie::~Sortie()
{
    //dtor
}

int Sortie::action()
{

    game->setCurrentScene(m_destination);
    player.setPosition(m_x,m_y);
    return EXIT_MAP;
}

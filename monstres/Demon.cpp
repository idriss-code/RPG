#include "Demon.h"
#include <SDL_image.h>

Demon::Demon():IAbasic("Demon",30)
{
    m_resist[FEU]=SENSIBL;
    if (! counter++)m_sprite=IMG_Load("./data/sprite/demon.png");


    //ctor
}

Demon::~Demon()
{
    //dtor
    if(! --counter)SDL_FreeSurface(m_sprite);
}


SDL_Surface * Demon::m_sprite=NULL;
int Demon::counter=0;

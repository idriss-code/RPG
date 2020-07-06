#include "Dragon.h"
#include <SDL_image.h>

Dragon::Dragon():IAbasic("Dragon")
{
    m_resist[FEU]=ABSORB;
    m_resist[EAU]=SENSIBL;
    m_force=2;

    if (! counter++)m_sprite=IMG_Load("./data/sprite/dragon.png");
    //ctor
}

Dragon::~Dragon()
{
    //dtor
    if(! --counter)SDL_FreeSurface(m_sprite);
}

SDL_Surface * Dragon::m_sprite=NULL;
int Dragon::counter=0;

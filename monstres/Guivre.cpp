#include "Guivre.h"
#include <SDL_image.h>

Guivre::Guivre():IAbasic("Guivre")
{
    m_resist[TERRE]=SENSIBL;
    m_force=3;

    if (! counter++)m_sprite=IMG_Load("./data/sprite/guivre.png");

    //ctor
}

Guivre::~Guivre()
{
    //dtor
    if(! --counter)SDL_FreeSurface(m_sprite);
}

SDL_Surface * Guivre::m_sprite=NULL;
int Guivre::counter=0;

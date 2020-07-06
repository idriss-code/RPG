#include "Player.h"

extern SDL_Window *ecran;

Player::Player()
{
    m_sprite=IMG_Load("./data/sprite/hero.png");
    source.h=m_height=16;
    source.w=m_width=16;

    //init();

    //ctor
}

void  Player::init()
{
    m_posX=65 ;
    m_posY=65 ;
    source.x=0;
    source.y=0;
}


Player::~Player()
{
    SDL_FreeSurface(m_sprite);
    //dtor
}

void Player::affiche(SDL_Rect *hitBox)
{
    SDL_BlitSurface(m_sprite,&source,SDL_GetWindowSurface(ecran),hitBox);
}

bool Player::deplace(int velX, int velY)
{
    if (velX>0)source.y=0;
    else if (velX<0)source.y=m_height*3;
    else if (velY>0)source.y=m_height*2;
    else if (velY<0)source.y=m_height*1;
    m_posX+=velX;
    m_posY+=velY;
    if (velX || velY){
        source.x=(source.x+=m_width)<m_width*2?source.x:0;
       return true;
    } else{

        return false;
    }
}

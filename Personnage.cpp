#include "Personnage.h"

Personnage::Personnage(const char*n,int pv,int mp):Entite(n,pv,mp),m_lvl(1)
{

        m_xp=0;
        m_xpLvlSuivant=m_lvl*XP_LVL;
    //ctor

}

Personnage::~Personnage()
{
    SDL_FreeSurface(m_sprite);
    //dtor
}

int Personnage::gainXp(int val)
{
    int i=0;
    m_xp+=val;
    while(m_xp>=m_xpLvlSuivant){
        lvlUp();
        m_xp-=m_xpLvlSuivant;
        m_xpLvlSuivant=m_lvl*XP_LVL;
        i=1;
    }
    return i;
}

void Personnage::lvlUp(){
    m_lvl++;
    m_force++;
    m_magie++;
    m_defPhys++;
    m_defMag++;

    m_PV=m_PVMax=m_PVMax*1.2;
    m_MP=m_MPMax=m_MPMax*1.2;
}

void Personnage::reset()
{
    m_anim=0;
    m_degatRecu=0;
    m_timer=0;
    this->position()=this->positionInit();
    this->cooldown()=this->cooldownMax();
}

void Personnage::afficheMenu(SDL_Rect position)
{
    SDL_UpperBlit(this->sprite(),NULL,SDL_GetWindowSurface(ecran),&position);
}

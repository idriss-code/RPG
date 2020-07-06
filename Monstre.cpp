#include "Monstre.h"
#include "constante.h"
#include "Group.h"

Monstre::Monstre(const char*n,int pv,int mp,int xp):Entite(n,pv,mp),m_XP(xp)
{
    //ctor
    setCooldownMax(300);
}

Monstre::~Monstre()
{
    //dtor
}

void Monstre::comportement(Group &attaquant,Group &defense){
    //  attaque toujour la premere cible valide (en haut)
    setCapaActive(0);
    setgrpcible(&defense);
    for(int u=0;u<NBGRP;u++)
        {
            if (defense[u]->PV()>0)  {setcible(u);break;}
        }
}

void Monstre::mort(){
if (m_transparence>0)m_transparence-=5;
if (m_transparence<0)m_transparence=0;
}

void Monstre::reset()
{
    m_PV=m_PVMax;
    m_MP=m_MPMax;
    m_degatRecu=0;
    m_anim=0;
    m_degatRecu=0;
    m_timer=0;
    this->position()=this->positionInit();
    this->cooldown()=this->cooldownMax();
    m_transparence=255;
}

void Monstre::affichePV_MP(TTF_Font *police)
{
    if (m_PV>0)Entite::affichePV_MP(police);
}

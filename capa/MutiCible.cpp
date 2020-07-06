#include "MutiCible.h"
#include "../Group.h"

MutiCible::MutiCible()
{
    setName("Quake");
    setMana(5);
    setmultiple();
    //ctor
}

MutiCible::~MutiCible()
{
    //dtor
}

void MutiCible::update(Entite &attaquant,Group &group,int cible)
{
    for(int u=0;u<NBGRP;u++)
        {
            if(group[u]!=NULL)if (group[u]->PV()>0)
            {
                attaquant.degat(group[u],TERRE,true);
            }
        }
attaquant.setAnim(0);
}

void MutiCible::draw()
{

}

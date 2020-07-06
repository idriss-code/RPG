#include "IAbasic.h"
#include "../constante.h"
#include "../Group.h"
#include "../util/benrandom.h"


IAbasic::IAbasic(const char*n,int pv,int mp,int xp):Monstre(n,pv,mp,xp)
{
    //ctor
}

IAbasic::~IAbasic()
{
    //dtor
}


void IAbasic::comportement(Group &attaquant,Group &defense){
    //  attaque au hazard cible valide
    setCapaActive(0);
    setgrpcible(&defense);

    int u=0;
    do{
            u=random(NBGRP-1);
    }while(defense[u]==NULL||defense[u]->PV()<=0);

    setcible(u);
}


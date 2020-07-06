#include "Soin.h"
#include "../Group.h"
#include "../constante.h"
extern SDL_Window *ecran;//  main.cpp

Soin::Soin()
{
    setName("soin");
    setMana(5);
    setgroupe(HERO);
    //ctor
}

Soin::~Soin()
{
    //dtor
}
void Soin::update(Entite &attaquant,Group &group,int cible){
    if (attaquant.anim()==0)
    {
            attaquant.setAnim(1);
            attaquant.cooldown()=attaquant.cooldownMax();
    }

    atqX = attaquant.position().x+attaquant.sprite()->w/2;
    atqY = attaquant.position().y+attaquant.sprite()->h/2;
    defX = group[cible]->position().x+group[cible]->sprite()->w/2;
    defY = group[cible]->position().y+group[cible]->sprite()->h/2;

    timer++;
    if(timer == 1&&group[cible]->PV()>0)group[cible]->gainPV(30);//  gain pv 1ere frame
    if(timer == 20){attaquant.setAnim(0);timer=0;}//  fin anime 20eme fram
}

void Soin::draw()
{
               for(int i=0;i<10;i++)
                {
                  ligne(SDL_GetWindowSurface(ecran),
                            atqX,atqY+i,defX,defY+i,
                            SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,150+timer*5,255,0));
                }
}

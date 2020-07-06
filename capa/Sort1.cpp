#include "Sort1.h"
#include "../Group.h"
extern SDL_Window *ecran;//  main.cpp

Sort1::Sort1()
{
    //ctor
    setName("sort FEU 1");
    setMana(5);
}

Sort1::~Sort1()
{
    //dtor
}

void Sort1::update(Entite &attaquant,Group &group,int cible)
{
    if (attaquant.anim()==1)//  debut animation et vérif si perso dispo
    {
            attaquant.setAnim(2);
            attaquant.cooldown()=attaquant.cooldownMax();
    }

    atqX = attaquant.position().x+attaquant.sprite()->w/2;
    atqY = attaquant.position().y+attaquant.sprite()->h/2;
    defX = group[cible]->position().x+group[cible]->sprite()->w/2;
    defY = group[cible]->position().y+group[cible]->sprite()->h/2;

   timer++;
   if(timer == 1)attaquant.degat(group[cible],FEU,true);//  perte de point de vie a la premiere frame
   if(timer == 20){attaquant.setAnim(0);timer=0;}//  fin de l'anim apres 20 frame
}

void Sort1::draw()
{
    for(int i=0;i<10;i++)
    {
      ligne(SDL_GetWindowSurface(ecran),
                atqX,atqY+i,defX,defY+i,
                SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,150+timer*5,200-timer*5,0));
    }
}

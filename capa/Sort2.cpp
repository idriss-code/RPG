#include "Sort2.h"
#include <SDL_image.h>

extern SDL_Window *ecran;//  main.cpp


Sort2::Sort2():drawSprite(false)
{
    setName("sort FEU 2");
    setMana(10);

    if (! counter++)sprite=IMG_Load("./data/sprite/explo.png");
    //ctor
}

Sort2::~Sort2()
{
    if(! --counter)SDL_FreeSurface(sprite);
    //dtor
}

SDL_Surface * Sort2::sprite=NULL;
int Sort2::counter=0;

void Sort2::update(Entite &attaquant,Group &group,int cible)
{

        if (attaquant.anim()==1)//  debut animation et vérif si perso dispo
        {
            attaquant.setAnim(2);
            attaquant.cooldown()=attaquant.cooldownMax();
        }
        if (attaquant.anim()==2)//  animation 1 allé vers position de tir
        {
            attaquant.position()=Trajectoire(attaquant.position().x,attaquant.position().y,
                                             SDL_GetWindowSurface(ecran)->w/4,SDL_GetWindowSurface(ecran)->h/3,10);//  ??? voir si lancé par monstre ???
            if (attaquant.position().x==SDL_GetWindowSurface(ecran)->w/4&&attaquant.position().y==SDL_GetWindowSurface(ecran)->h/3)
            {
                drawSprite=true;
                attaquant.setAnim(3);
                position.x=SDL_GetWindowSurface(ecran)->w/4;
                position.y=SDL_GetWindowSurface(ecran)->h/3;
            }
        }
        if (attaquant.anim()==3)//  animation 2 tir
        {
           attaquant.position().x=SDL_GetWindowSurface(ecran)->w/4;
           attaquant.position().y=SDL_GetWindowSurface(ecran)->h/3;
           position=Trajectoire(position.x,position.y,
                                group[cible]->position().x+group[cible]->sprite()->w/2-sprite->w/2,
                                group[cible]->position().y+group[cible]->sprite()->h/2-sprite->h/2,
                                10);
           if(position.x==group[cible]->position().x+group[cible]->sprite()->w/2-sprite->w/2
              &&
              position.y==group[cible]->position().y+group[cible]->sprite()->h/2-sprite->h/2)
           {
               drawSprite=false;
               attaquant.setAnim(4);
               attaquant.degat(group[cible],FEU,true,25);//  perte de PV
           }
        }
        if (attaquant.anim()==4)//  animation 3 retour
        {
            attaquant.position()=Trajectoire(attaquant.position().x,attaquant.position().y,
                                             attaquant.positionInit().x,attaquant.positionInit().y,10);
            if (attaquant.position().x==attaquant.positionInit().x &&attaquant.position().y==attaquant.positionInit().y)
            {
               attaquant.setAnim(0);
            }//  fin retour  perso pret
        }
}
void Sort2::draw()
{
    if(drawSprite)SDL_UpperBlit(sprite,NULL,SDL_GetWindowSurface(ecran),&position);
}

#include "XpScene.h"
#include <iostream>
#include "../core/Game.h"
#include "../Monstre.h"
#include "../Personnage.h"

extern TTF_Font* numberFont;
extern TTF_Font* texteFont;
extern SDL_Color NOIR ;//  fonctionTTF.cpp
extern SDL_Color VERT ;
extern Group hero;

XpScene::XpScene(Group* MOnstre,Scene* parent):Scene(parent),monstre(MOnstre)
{
    //ctor
    setRGB(50,50,100);
    delayInit=3;
}

XpScene::~XpScene()
{
    //dtor
}

void XpScene::load()
{
  std::cerr<<"load XpScene"<<std::endl;
  delay = delayInit;
  xpTotal=0;
    for(int i=0;i<NBGRP;i++){
        if((*monstre)[i]!=NULL){
                xpTotal+=dynamic_cast<Monstre*>((*monstre)[i])->xp();
        }
        xp[i]=0;
        xpS[i]=30;
        lvlUp[i]=0;
    }

    for(int i=0;i<NBGRP;i++)
    {
        if(hero[i]!=NULL)
        {
            hero[i]->reset();
            barreCool[i]=new Barre(xp[i],xpS[i]);
            barreCool[i]->setPosition(hero[i]->position().x+50,hero[i]->position().y+35);
        }
    }
}

void XpScene::unload()
{
    std::cerr<<"unload XpScene"<<std::endl;
    for(int i=0;i<NBGRP;i++)
    {
        if(hero[i]!=NULL)
        {
            delete barreCool[i];
        }
    }
}

void XpScene::update(int dt)
{
    switch(event.type)
            {
                case SDL_QUIT:
                    game->quit();
                    break;
                case SDL_KEYDOWN:
                    //exit();
                    break;
            }

            delay--;
            if (delay<=0){
                    xpTotal--;
                    delay=delayInit;
                    for(int i=0;i<NBGRP;i++)
                    {
                        if(hero[i]!=NULL)
                        {
                            if(dynamic_cast<Personnage *>(hero[i])->gainXp(1))lvlUp[i]=1;
                            xp[i]=dynamic_cast<Personnage *>(hero[i])->xp();
                            xpS[i]=dynamic_cast<Personnage *>(hero[i])->xpLvlSuivant();
                        }
                    }
            }



    if (xpTotal <= 0)loop=0;
    if(game->status()==QUIT)loop = 0;
}

void XpScene::draw()
{
        SDL_Rect position;

        for(int i=0;i<NBGRP;i++)
        {
            if(hero[i]!=NULL)
            {
                hero[i]->afficheSprite();
                barreCool[i]->afficheGD(ecran);
                position.x=hero[i]->position().x+50;
                position.y=hero[i]->position().y;
                afficheTexte(position,hero[i]->nom(),ecran,texteFont,NOIR);
                position.x=hero[i]->position().x+150;
                position.y=hero[i]->position().y;
                if (lvlUp[i])afficheTexte(position,"Level UP",ecran,texteFont,VERT);
                position.x=hero[i]->position().x+50;
                position.y=hero[i]->position().y+15;
                afficheIntSurInt(position,xp[i],xpS[i],ecran,numberFont,NOIR);
            }
        }
}

void XpScene::loach(Group* Monstre,Scene* parent)
{
    std::cerr<<"loach XpScene"<<std::endl;
    Scene* xpScene = new XpScene(Monstre,parent);
    xpScene->exec();
    delete xpScene;
}

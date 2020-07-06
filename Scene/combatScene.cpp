#include "combatScene.h"
#include <iostream>
#include "../core/Game.h"
#include "../util/Barre.h"
#include "../Monstre.h"
#include "MenuScene.h"
#include "GameOver.h"
#include "XpScene.h"

extern TTF_Font* numberFont;
extern TTF_Font* texteFont;
extern SDL_Color NOIR ;//  fonctionTTF.cpp
extern SDL_Color VERT ;
extern Group hero;


combatScene::combatScene(Group *monstres,Scene* parent): Scene(parent),monstre(*monstres)
{
    //ctor
}

combatScene::~combatScene()
{
    //dtor
}
void combatScene::load()
{
    setRGB(50,100,50);

    selection=SDL_CreateRGBSurface(0,4,4,32,0,0,0,0);//  petit carré de séléction
    returnVal=PLAY;
    timerFin=45;
    menu=PERSO;//  position dans le menu
    selectHero=0,selectCapa=0,cible=0,groupecible=MONSTRE;//  selectHero= hero selectioner / selectCapa= sort séléctioner / cible séléctioner

    groupe[0]=hero;
    groupe[1]=monstre;

    for(int u=0;u<NBGRP;u++)
    {
        if(hero[u]!=NULL)
        {

            hero[u]->positionInit().x=DIST_HERO;
            hero[u]->positionInit().y=u*120+20;
            hero[u]->reset();
            barreCool[u]=new Barre(hero[u]->cooldown(),hero[u]->cooldownMax());
            barreCool[u]->setPosition(20,SDL_GetWindowSurface(ecran)->h-50+u*15);
        }

    }
    for(int u=0;u<NBGRP;u++)
    {
        if(monstre[u]!=NULL)
        {
            monstre[u]->positionInit().x=550;//?????????????????????????????
            monstre[u]->positionInit().y=u*120+20;
            monstre[u]->reset();
            monstre[u]->cooldown()=monstre[u]->cooldownMax()/(u+1);
        }

    }
        std::cerr<<"load combat"<<std::endl;
}

void combatScene::unload()
{
    for(int u=0;u<4;u++)if(hero[u]!=NULL)delete barreCool[u];
        std::cerr<<"unload combat"<<std::endl;
}

void combatScene::update(int dt)
{
    int xmenu=0;
    int monstrevivant=0;
    int heroVivant=0;

    //  vérif de qui est vivant
        if (hero[selectHero]->PV()<=0)menu=PERSO;// retour au menu PERSO si select hero est mort
        for(int u=monstrevivant=heroVivant=0;u<NBGRP;u++)
        {
            if(monstre[u]!=NULL)if (monstre[u]->PV()>0)monstrevivant++;
            if(hero[u]!=NULL)if (hero[u]->PV()>0)heroVivant++;
        }
//  gestion du menu si une cible ou un hero est mort
        if (!heroVivant||!monstrevivant)menu=LOCK;// blocl le menu sdi fin de combat
        if(heroVivant)while(hero[selectHero]==NULL||hero[selectHero]->PV()<=0){selectHero++;if (selectHero>=NBGRP)selectHero=0;}
        while(monstrevivant&&(groupe[groupecible][cible]==NULL||(groupecible==MONSTRE&&monstre[cible]->PV()<=0)))
            {cible++;if (cible>=NBGRP)cible=0;};

            switch(event.type)
            {
                case SDL_QUIT:
                    game->quit();
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)//  Gestion des touches du clavier
                    {
                        case SDLK_ESCAPE:
                            event.key.keysym.sym=0;//evite les pb de repetition de touche
                            xmenu=1;
                            break;
                        case SDLK_RIGHT:
                             event.key.keysym.sym=0;//evite les pb de repetition de touche
                             if (menu==CIBLE){
                                    groupecible=MONSTRE;
                                    cible=0;
                                    while(monstrevivant&&(groupe[groupecible][cible]==NULL||(groupecible==MONSTRE&&monstre[cible]->PV()<=0))){cible++;if (cible>=NBGRP)cible=0;};
                             }
                            break;
                        case SDLK_LEFT:
                             event.key.keysym.sym=0;//evite les pb de repetition de touche
                             if (menu==CIBLE){
                                    groupecible=HERO;
                                    cible=0;
                             }
                            break;
                        case SDLK_UP:
                            event.key.keysym.sym=0;//evite les pb de repetition de touche
                            if(menu==PERSO)
                            {
                                do{
                                    selectHero= --selectHero>=0?selectHero:NBGRP-1;
                                }while(hero[selectHero]==NULL||hero[selectHero]->PV()<=0);
                            }
                            else if (menu==SORT&&hero[selectHero]->capa(selectCapa-1)!=NULL&&selectCapa>0)selectCapa--;
                            else if(menu==CIBLE)
                                    do {cible= --cible>=0?cible:NBGRP-1;
                                    }while(groupe[groupecible][cible]==NULL||(groupecible==MONSTRE&&monstre[cible]->PV()<=0));
                            break;
                        case SDLK_DOWN:
                            event.key.keysym.sym=0;//evite les pb de repetition de touche
                            if (menu==PERSO){
                                do{
                                    selectHero= ++selectHero<NBGRP?selectHero:0;
                                }while(hero[selectHero]==NULL||hero[selectHero]->PV()<=0);
                            }
                            else if (menu==SORT&&hero[selectHero]->capa(selectCapa+1)!=NULL&&selectCapa<NBCAPA-1)selectCapa++;
                            else if (menu==CIBLE)do {
                                    cible= ++cible<NBGRP?cible:0;
                                    if (cible>=NBGRP)cible=0;
                            }while(groupe[groupecible][cible]==NULL||(groupecible==MONSTRE&&monstre[cible]->PV()<=0));
                            break;
                        case SDLK_RETURN:
                            // verification a chaque fois si je peu passer aun menu suivant
                            //  ???????????? voir pour un case ???????????
                            event.key.keysym.sym=0;

                            if (menu==PERSO&&!hero[selectHero]->anim()&&!hero[selectHero]->cooldown())menu=SORT;//  selection du hero
                                                                                                //  si  "anime" = 0 et coodown = 0 passage a la selction capa
                            else if (menu==SORT){//  selction capa
                                if(hero[selectHero]->MP()>=hero[selectHero]->capa(selectCapa)->mana())menu=CIBLE;//  si sufisament de MP et passge au choix de la cible
                                groupecible=hero[selectHero]->capa(selectCapa)->groupecible();//  permet au capa de soin de cible auto amie

                                }
                            else if (menu==CIBLE){//  choix de la cible

                                hero[selectHero]->setAnim(1);//  met en route la capa
                                hero[selectHero]->setCapaActive(selectCapa);
                                hero[selectHero]->setcible(cible);
                                hero[selectHero]->setgrpcible(&groupe[groupecible]);
                                hero[selectHero]->looseMP(hero[selectHero]->capa(selectCapa)->mana());//  conssome la mana

                                menu=PERSO,selectCapa=0;
                                if(hero[selectHero+1]!=NULL)selectHero++;//  passage au hero suivant
                                else selectHero=0;
                            }
                            break;
                    }
                    break;
            }


            //gestion du menu
            if(xmenu){
                MenuScene::loach(NULL);
                xmenu=0;
            }

            //Gestion cooldown et action ENI

            for(int u=0;u<NBGRP;u++)
            {
                if(hero[u]!=NULL){
                    if (hero[u]->cooldown()!=0)hero[u]->cooldown()--;
                }
                if(monstre[u]!=NULL){
                    if(monstre[u]->PV()>0&&!monstre[u]->anim()&&!monstre[u]->cooldown())//  si le monsre est vivant et pret
                    {
                        monstre[u]->setAnim(1);
                        //  dynamique cast tranfome un pointeur entite en pointeur monrstre puis lance l'IA du monstre
                        dynamic_cast<Monstre *>(monstre[u])->comportement(monstre,hero);
                    }
                    if (monstre[u]->cooldown()!=0)monstre[u]->cooldown()--;
                }
            }

            //  Gestion des capa

           for(int j=0;j<NBGRP;j++){
                if (hero[j]!=NULL && hero[j]->anim()!=0){
                    hero[j]->capa(hero[j]->capaActive())->update(*hero[j],*hero[j]->grpcible(),hero[j]->cible());
                }
                if (monstre[j]!=NULL && monstre[j]->anim()!=0){
                    monstre[j]->capa(monstre[j]->capaActive())->update(*monstre[j],*monstre[j]->grpcible(),monstre[j]->cible());
                }
                if (monstre[j]!=NULL && monstre[j]->PV()<=0){
                        monstre[j]->mort();
                }
                if (hero[j]!=NULL && hero[j]->PV()<=0){
                        hero[j]->mort();
                }
           }
         //  Gestion fin de combat
           if (!heroVivant||!monstrevivant){
                timerFin--;
                if (timerFin<=0)loop=0;
        }

        if (loop==0){
            if (game->status()==PLAY){
                if(heroVivant)XpScene::loach(&monstre);
                if (monstrevivant){std::cerr<<"GAME OVER"<<std::endl;GameOver::loach();}
            }
        }
}

void combatScene::draw()
{
    //DRAW
            SDL_Rect position;
//  affichage pointeur selection
            if (menu!=PERSO)SDL_FillRect(selection,NULL,SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,50,0,50));
            if (menu==PERSO)SDL_FillRect(selection,NULL,SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,250,0,50));
            SDL_UpperBlit(selection,NULL,SDL_GetWindowSurface(ecran),&hero[selectHero]->position());
            if (menu==CIBLE)
                {
                    SDL_FillRect(selection,NULL,SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,250,0,50));
                    if(menu==CIBLE&&hero[selectHero]->capa(selectCapa)->cible()==UNIQUE)SDL_UpperBlit(selection,NULL,SDL_GetWindowSurface(ecran),&groupe[groupecible][cible]->position());
                    else if(menu==CIBLE&&hero[selectHero]->capa(selectCapa)->cible()==MULTI)
                    {
                        for(int u=0;u<NBGRP;u++)
                        {
                            if(groupe[groupecible][u]!=NULL)if (groupe[groupecible][u]->PV()>0)
                            {
                                SDL_UpperBlit(selection,NULL,SDL_GetWindowSurface(ecran),&groupe[groupecible][u]->position());
                            }
                        }
                    }
                }

//  affichage des perso et mosnstre, et gestion cooldown
            for(int u=0;u<NBGRP;u++)
            {
                if(hero[u]!=NULL){
                    //  affichage sprite PV MP
                    hero[u]->afficheSprite();
                    hero[u]->affichePV_MP(numberFont);
                    //  afffichage dégat et soin
                    hero[u]->afficheSoin(numberFont);
                    hero[u]->afficheDegats(numberFont);
                    //  afffichage et gestion cooldown
                    barreCool[u]->afficheGDInv(ecran);
                }
                if(monstre[u]!=NULL){
                    //  affichage sprite PV MP
                    monstre[u]->afficheSprite();
                    monstre[u]->affichePV_MP(numberFont);
                    //  afffichage dégat et soin
                    monstre[u]->afficheSoin(numberFont);
                    monstre[u]->afficheDegats(numberFont);
                    //  afffichage et gestion cooldown
                }
            }
//  Dessin des capa

           for(int j=0;j<NBGRP;j++){
                if (hero[j]!=NULL && hero[j]->anim()!=0){
                    hero[j]->capa(hero[j]->capaActive())->draw();
                }
                if (monstre[j]!=NULL && monstre[j]->anim()!=0){
                    monstre[j]->capa(monstre[j]->capaActive())->draw();
                }
           }

//  affichage des menus
            position.x=150;
            position.y=SDL_GetWindowSurface(ecran)->h-50;
            if(menu==SORT)afficheTexte(position,hero[selectHero]->capa(selectCapa)->name(),ecran,texteFont,NOIR);
            if(menu==CIBLE&&hero[selectHero]->capa(selectCapa)->cible()==UNIQUE)afficheTexte(position,groupe[groupecible][cible]->nom(),ecran,texteFont,NOIR);
            else if(menu==PERSO)afficheTexte(position,hero[selectHero]->nom(),ecran,texteFont,NOIR);
}


void combatScene::loach(Group *monstre,Scene* parent)
{
    combatScene combat(monstre,parent);
    combat.exec();
}

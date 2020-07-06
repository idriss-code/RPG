#include "AffichePerso.h"

#include "../constante.h"
#include "../util/Barre.h"
#include "../Group.h"
#include "../Monstre.h"
#include "../Personnage.h"
#include "../core/Game.h"
extern Game* game;

extern SDL_Window *ecran;//  main.cpp
extern TTF_Font* numberFont;
extern TTF_Font* texteFont;
extern SDL_Color NOIR ;//  fonctionTTF.cpp
extern SDL_Color VERT ;
extern Group hero;

AffichePerso::AffichePerso(const char* name):ElementMenu(name)
{
    //ctor
}

AffichePerso::~AffichePerso()
{
    //dtor
}

int AffichePerso::action(int val)
{

    int initX=100;
    int initY=100;
    int realY=0;
    int interLigne=20;
    int interMot=35;
    int firstCol=100;
    int secCol=250;
    int interRow=100;


    SDL_Event evenement;
    int continuer=1;

    while(continuer){
//UPDATE
            SDL_PollEvent(&evenement);
            switch(evenement.type)
            {
                case SDL_QUIT:
                    game->quit();
                    break;
                case SDL_KEYDOWN:
                    continuer=0;
                    break;


            }

        SDL_FillRect(SDL_GetWindowSurface(ecran),NULL,SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,50,50,100));
//DRAW
        SDL_Rect position;
        for(int u=0;u<NBGRP;u++)
        {
            if(hero[u]!=NULL)
            {
                realY=initY+u*interRow;

                position.x=initX;
                position.y=realY;
// affichage du sprite
                dynamic_cast<Personnage *>(hero[u])->afficheMenu(position);
// affichage du nom
                position.x=initX+firstCol;
                position.y=realY;
                afficheTexte(position,hero[u]->nom(),ecran,texteFont,NOIR);

// afichage xp et LVL
                position.y+=interLigne;
                afficheTexte(position,"LVL",ecran,texteFont,NOIR);
                position.x+=interMot;
                afficheInt(position,dynamic_cast<Personnage *>(hero[u])->lvl(),ecran,numberFont,NOIR);
                position.x=initX+firstCol;
                position.y+=interLigne;
                afficheTexte(position,"XP",ecran,texteFont,NOIR);
                position.x+=interMot;
                afficheIntSurInt(position,dynamic_cast<Personnage *>(hero[u])->xp(),dynamic_cast<Personnage *>(hero[u])->xpLvlSuivant(),ecran,numberFont,NOIR);
// affichage de PV et MP
                position.x=initX+secCol;
                position.y=realY+interLigne;
                afficheTexte(position,"PV",ecran,texteFont,NOIR);
                position.x+=interMot;
                afficheIntSurInt(position,hero[u]->PV(),hero[u]->PVMax(),ecran,numberFont,NOIR);
                position.x=initX+secCol;
                position.y+=interLigne;
                afficheTexte(position,"MP",ecran,texteFont,NOIR);
                position.x+=interMot;
                afficheIntSurInt(position,hero[u]->MP(),hero[u]->MPMax(),ecran,numberFont,NOIR);
            }
        }

        SDL_UpdateWindowSurface(ecran);
        SDL_Delay(100);
        if(game->status()==QUIT)continuer = 0;
    }
    return 0;
}


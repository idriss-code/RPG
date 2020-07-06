#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "util/fonctionDessin.h"
#include "util/fonctionTTF.h"
#include "util/benrandom.h"
#include "constante.h"

extern SDL_Color GRIS ;//  fonctionTTF.cpp
extern SDL_Color BLANC ;
extern SDL_Color JAUNE ;

extern SDL_Window *ecran;//  main.cpp

void affichPlan(SDL_Surface *ecran,SDL_Surface*plan,SDL_Rect* position,SDL_Rect* scroll1,SDL_Rect* scroll2,int repet,int vitesse,int hauteur);

int intro()
{
    //setrand();
    //int tps=0,tps2=0;
    int i,pass=0,r=0,g=0,b=0;
    int returnVal=PLAY;
    bool clignote = true;

    SDL_Surface *ligne[256];
    SDL_Surface *plan=NULL;
    SDL_Surface *plan2=NULL;
    SDL_Surface *plan3=NULL;
    SDL_Surface *lune=NULL;
    SDL_Surface *alpha=NULL;

    SDL_Rect position;
    SDL_Rect scroll1={0};
    SDL_Rect scroll2={0};
    SDL_Rect scroll21={0};
    SDL_Rect scroll22={0};
    SDL_Rect scroll31={0};
    SDL_Rect scroll32={0};
//gestion texte
    TTF_Font*Font=TTF_OpenFont("data/Medici.ttf",100);
    TTF_Font*Font2=TTF_OpenFont("data/Fette.ttf",25);
    if(!Font || !Font2)
    {
        cerr<<"TTF_OpenFont: "<< TTF_GetError()<<endl;
        return 0;
    }
    SDL_Surface *titre=TTF_RenderText_Blended(Font,"DonjonFantasy",JAUNE);
    SDL_Surface *titreShadow=TTF_RenderText_Blended(Font,"DonjonFantasy",GRIS);
    SDL_Surface *texte=TTF_RenderText_Blended(Font2,"Benlamouche présente",GRIS);
    SDL_Surface *texte2=TTF_RenderText_Blended(Font2,"Press Key",BLANC);


//gestion
    int luneObj=SDL_GetWindowSurface(ecran)->h*7/12;
    plan3= IMG_Load("data/intro/montagne.png");
    plan2 = IMG_Load("data/intro/foreground.png");
    plan= IMG_Load("data/intro/ground.png");
    lune= IMG_Load("data/intro/lune.png");

	if(!plan || !plan2 || !plan3 || !lune){
        cerr<<"PB open intro sprite: "<< SDL_GetError()<<endl;
		return 0;
	}

    scroll1.w=plan->w;
    scroll1.h=plan->h;
    scroll2=scroll1;
    scroll2.x=-plan->w;

    scroll21.w=plan2->w;
    scroll21.h=plan2->h;
    scroll22=scroll21;
    scroll22.x=-plan2->w;

    scroll31.w=plan3->w;
    scroll31.h=plan3->h;
    scroll32=scroll31;
    scroll32.x=-plan3->w;

    position.x=0;

    //  surface éfassant les étoile

    alpha=SDL_CreateRGBSurface(0,SDL_GetWindowSurface(ecran)->w,SDL_GetWindowSurface(ecran)->h,32,0,0,0,0);
    SDL_SetSurfaceBlendMode(alpha,SDL_BLENDMODE_BLEND);
    SDL_FillRect(alpha,NULL,SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,r,g,b));

    for(i=0;i<255;i++)
        {
            ligne[i]=SDL_CreateRGBSurface(0,SDL_GetWindowSurface(ecran)->w,3,32,0,0,0,0);
        }
// musique
    Mix_Music *musique;
    musique = Mix_LoadMUS("data/music/test.mp3");
    if(!musique) {
    cerr<<"TTF_OpenFont: "<< Mix_GetError()<<endl;
    // this might be a critical error...
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
    Mix_PlayMusic(musique,-1);

    Mix_Chunk *sample;
    sample=Mix_LoadWAV("data/son/LASER.WAV");
    if(!sample) {
        cerr<<"Mix_LoadWAV: "<< Mix_GetError()<<endl;
        // handle error
    }
    Mix_PlayChannel(-1, sample, 0);

    int continuer=1;
    SDL_Event evenement;// variable evenement

    while(continuer)
    {

        // UPDATE
            SDL_PollEvent(&evenement);
            switch(evenement.type)
            {

                case SDL_QUIT:
                    continuer=0;
                    returnVal=QUIT;
                    break;
                case SDL_KEYDOWN:
                    continuer=0;
                    break;
            }
//  DRAW
            if(pass<luneObj){
                SDL_FillRect(SDL_GetWindowSurface(ecran),NULL,SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,0,0,0));
            }
//dégradé

            if(pass<luneObj){
                for(i=0;i<255;i++)
                {
                    r=i-pass/2;
                    if(r>=255)r=255;
                    if(r<=0)r=0;
                    g=i-pass;
                    if(g>=255)g=255;
                    if(g<=0)g=0;
                    b=i+30-pass/2;
                    if(b>=255)b=255;
                    if(b<=0)b=0;
                    SDL_FillRect(ligne[i],NULL,SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,r,g,b));
                    position.x=0;
                    position.y=i*3;
                    SDL_UpperBlit(ligne[i],NULL,SDL_GetWindowSurface(ecran),&position);
                }
            }
//étoile
            else if(pass>luneObj)
            {
                r=g=b=0;
                int a=1;
                SDL_SetSurfaceAlphaMod(alpha,a);

                position.x=0;
                position.y=0;
                SDL_UpperBlit(alpha,NULL,SDL_GetWindowSurface(ecran),&position);

                for(i=0;i<2;i++)
                {
                    int x=random(SDL_GetWindowSurface(ecran)->w,1);
                    int y=random(SDL_GetWindowSurface(ecran)->h,1);
                    setPixelVerif(SDL_GetWindowSurface(ecran),x,y,SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,255,255,255));
                }
            }

//lune
            position.x=SDL_GetWindowSurface(ecran)->w/2-lune->w/2;
            int luneY=pass<luneObj?pass:luneObj;
            position.y=SDL_GetWindowSurface(ecran)->h-SDL_GetWindowSurface(ecran)->h/3-luneY;
            if(position.y+lune->h-1>0)
            SDL_UpperBlit(lune,NULL,SDL_GetWindowSurface(ecran),&position);
// 3eme plan

            position.x=0;
            position.y=0;
            position.h=SDL_GetWindowSurface(ecran)->h;
            position.w=SDL_GetWindowSurface(ecran)->w;
            SDL_BlitScaled(plan3,NULL,SDL_GetWindowSurface(ecran),&position);

            //affichPlan(SDL_GetWindowSurface(ecran),plan3,&position,&scroll31,&scroll32,2,5,0);
// 2eme plan

            affichPlan(SDL_GetWindowSurface(ecran),plan2,&position,&scroll21,&scroll22,2,2,0);
// premier plan

            affichPlan(SDL_GetWindowSurface(ecran),plan,&position,&scroll1,&scroll2,2,5,0);
// texte

            if(pass>luneObj && pass<luneObj+50)
            {
                position.x=30;
                position.y=30;
                SDL_UpperBlit(texte,NULL,SDL_GetWindowSurface(ecran),&position);
            }
            if(pass>luneObj+100)
            {
                int hauteur=65;
                position.x=SDL_GetWindowSurface(ecran)->w/2-titre->w/2+5;
                position.y=pass-luneObj-200<hauteur+5?pass-luneObj-200:hauteur+5;
                SDL_UpperBlit(titreShadow,NULL,SDL_GetWindowSurface(ecran),&position);

                position.x=SDL_GetWindowSurface(ecran)->w/2-titre->w/2;
                position.y=hauteur;
                SDL_UpperBlit(titre,NULL,SDL_GetWindowSurface(ecran),&position);
            }
            int clignoteTest= pass%15;

            if(!clignoteTest){
                if(clignote)clignote=false;
                else clignote = true;
            }
            if(pass>luneObj+400 && clignote)
            {
                position.x=SDL_GetWindowSurface(ecran)->w/2-texte2->w/2;
                position.y=400;
                SDL_UpperBlit(texte2,NULL,SDL_GetWindowSurface(ecran),&position);
            }

            pass = ++pass>0?pass:0;//compte le nombre de rafraichssement
// rafraichissement
            SDL_UpdateWindowSurface(ecran);
            SDL_Delay(30);
    }

    Mix_HaltMusic();//stop la musique

// liberation memoire

    Mix_FreeMusic(musique);

    for(i=0;i<255;i++)
        {
            SDL_FreeSurface(ligne[i]);
        }
    SDL_FreeSurface(plan);
    SDL_FreeSurface(plan2);
    SDL_FreeSurface(plan3);
	SDL_FreeSurface(lune);
	SDL_FreeSurface(alpha);
	SDL_FreeSurface(titre);
    SDL_FreeSurface(titreShadow);
    SDL_FreeSurface(texte);
	SDL_FreeSurface(texte2);

	TTF_CloseFont(Font);
    TTF_CloseFont(Font2);

    return returnVal;
}

// fonction charger d'afficher un plan en scroll
void affichPlan(SDL_Surface *ecran,SDL_Surface*plan,SDL_Rect* position,SDL_Rect* scroll1,SDL_Rect* scroll2,int repet,int vitesse,int hauteur)
{
       //position->y=ecran->h-plan->h-hauteur;
            scroll1->x+=vitesse;
            scroll2->x+=vitesse;
          if(scroll1->x>=plan->w)
            {
                scroll1->x=0;
                scroll2->x=-plan->w;
            }
    int i;

for(i=0;i<repet;i++)
            {
                position->x=i*plan->w;
                position->y=ecran->h-plan->h-hauteur;
                SDL_UpperBlit(plan,scroll1,ecran,position);
                position->y=ecran->h-plan->h-hauteur;
                SDL_UpperBlit(plan,scroll2,ecran,position);
            }
}


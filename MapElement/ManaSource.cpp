#include "ManaSource.h"
#include "../util/fonctionDessin.h"
#include "../Group.h"

extern SDL_Window *ecran;//  main.cpp
extern Group hero;

ManaSource::ManaSource()
{
    actived=false;
}



ManaSource::~ManaSource()
{

}

int ManaSource::action()
{
    if(!actived){

        flash(ecran,50,SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,50,100,255));

        for(int i=0;i<NBGRP;i++)
        {
            if(hero[i]!=NULL)
            {
                hero[i]->GainMP(hero[i]->MPMax());
            }
        }
        actived=true;
    }

        return GO;
}

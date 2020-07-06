#include "TestScene.h"
#include "../core/Game.h"

#include <iostream>

TestScene::TestScene()
{
    //ctor
}

TestScene::~TestScene()
{
    //dtor
}


void TestScene::load()
{
    lune= IMG_Load("data/intro/lune.png");
    std::cerr<<"load"<<std::endl;
}

void TestScene::unload()
{
    SDL_FreeSurface(lune);
    std::cerr<<"unload"<<std::endl;
}

void TestScene::update(int dt)
{
        switch(event.type)
        {
            case SDL_QUIT:
                game->quit();
                break;
            case SDL_KEYDOWN:
                game->quit();
                break;
        }

        std::cerr<<"update" <<loop<<std::endl;
}

void TestScene::draw()
{
    std::cerr<<"draw"<<std::endl;
    SDL_Rect position;
    position.x=SDL_GetWindowSurface(ecran)->w/2-lune->w/2;
    position.y=SDL_GetWindowSurface(ecran)->h/2-lune->h/2;
    SDL_UpperBlit(lune,NULL,SDL_GetWindowSurface(ecran),&position);
    std::cerr<<"draw"<<std::endl;
}

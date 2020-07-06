#include "GameOver.h"
#include "../util/fonctionTTF.h"
#include "../core/Game.h"
#include <iostream>

extern TTF_Font* texteFont;
extern SDL_Color VERT ;

GameOver::GameOver(Scene* parent):Scene(parent)
{
    //ctor
}

GameOver::~GameOver()
{
    //dtor
}


void GameOver::load()
{
  std::cerr<<"load GameOver"<<std::endl;
}

void GameOver::unload()
{
    std::cerr<<"unload GameOver"<<std::endl;
    game->reset();
}

void GameOver::update(int dt)
{
    switch(event.type)
            {
                case SDL_QUIT:
                    game->quit();
                    break;
                case SDL_KEYDOWN:
                    exit();
                    break;
            }

    if(game->status()==QUIT)loop = 0;
}

void GameOver::draw()
{
    SDL_Rect position;
    position.x=300;
    position.y=300;
    afficheTexte(position,"GAME OVER",ecran,texteFont,VERT);
}

void GameOver::loach(Scene* parent)
{
    std::cerr<<"loach GameOver"<<std::endl;
    Scene* gameOver = new GameOver(parent);
    game->currentScene()->exit();
    game->setCurrentScene(gameOver);
}

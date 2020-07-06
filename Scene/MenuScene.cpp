#include "MenuScene.h"
#include "../core/Game.h"
#include "../menu/SousMenu.h"
#include "../menuItem/Quit.h"
#include "../menuItem/Continue.h"
#include "../menuItem/AffichePerso.h"
#include <iostream>

extern TTF_Font * menuFont;

MenuScene::MenuScene(Scene* parent): Scene(parent)
{
    //ctor
}

MenuScene::~MenuScene()
{
    //dtor
}

void MenuScene::load()
{
    mPrincipal= new Menu(200,100,menuFont,50);
    mPrincipal->addElement(new Continue("Continuer"));
    mPrincipal->addElement(new AffichePerso("Heros"));
    mPrincipal->addElement(new Quit("Quiter"));
    Menu::setMenuActif(mPrincipal);
    setRGB(50,100,100);
    if(parent()){
        switchClean();
    }
}

void MenuScene::unload()
{

}

void MenuScene::update(int dt)
{
    switch(event.type)
    {
        case SDL_QUIT:
            game->quit();
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    loop=0;
                    break;
                case SDLK_UP:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::menuActif()->up();
                    break;
                case SDLK_DOWN:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::menuActif()->down();
                    break;
                case SDLK_RETURN:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::activation();
                    break;
                case SDLK_BACKSPACE:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::setMenuActif(Menu::menuActif()->menuParent());
                    break;
            }
        break;
    }

    int returnVal =0;
    returnVal = Menu::updateMenu(returnVal);
    if(returnVal==PLAY){
        loop = 0;
    }
}

void MenuScene::draw()
{
    if(parent()){
        parent()->clean();
        parent()->draw();
    }

    Menu::menuActif()->affiche(ecran);
}

void MenuScene::loach(Scene* parent)
{
    MenuScene menuScene(parent);
    menuScene.exec();
}

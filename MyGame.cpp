#include "MyGame.h"

#include <iostream>
#include "constante.h"
#include "util/benrandom.h"
#include "menu/SousMenu.h"
#include "menuItem/Quit.h"
#include "menuItem/Continue.h"
#include "menuItem/AffichePerso.h"//non core

#include "core/Game.h"

#include "Player.h"

#include "capa/Frape.h"
#include "capa/Sort1.h"
#include "capa/Sort2.h"
#include "capa/Soin.h"
#include "capa/MutiCible.h"

#include "monstres/Dragon.h"
#include "monstres/Demon.h"
#include "monstres/Guivre.h"

#include "Map/FinalMap.h"
#include "MapElement/Wall.h"
#include "MapElement/Boss.h"
#include "MapElement/Sortie.h"
#include "MapElement/Switch.h"

#include "Personnage.h"

using namespace std;

// ************* variables globales ****************************
TTF_Font* numberFont=NULL;
TTF_Font* texteFont=NULL;
TTF_Font* menuFont=NULL;

Group hero;//???????  fusioner hero et player et incoporer initHero
Player player;

extern SDL_Color NOIR ;//  fonctionTTF.cpp
extern SDL_Color VERT ;

MyGame::MyGame()
{
    //ctor

// ***********  CHARGEMENT FONT **********************************

    numberFont=TTF_OpenFont("data/Fette.ttf",15);
    texteFont=TTF_OpenFont("data/Augusta.ttf",20);
    menuFont=TTF_OpenFont("data/Fette.ttf",30);


//*********************************** CHARGEMENT SCENE **********************************


    FinalMap* worldMap=new FinalMap("data/map/map.mp","data/map/wmap.png");
    worldMap->addElement(new Wall,0);
    worldMap->addMonstre(new Group(new Demon,new Demon,new Demon,new Demon));
    worldMap->addMonstre(new Group(new Demon,new Demon));
    worldMap->addMonstre(new Group(new Demon,new Dragon));


    FinalMap* cave=new FinalMap("data/map/cave.mp","data/map/cave.png");
    cave->addMonstre(new Group(new Demon,new Demon,new Demon,new Demon));
    cave->addElement(new Wall,0);
    //cave.addElement(new Boss(new Group(new Dragon,new Guivre)),3);
    //cave.addElement(new Switch(&cave,8,2,36,0),3);

    setTunnel(worldMap,2,cave,2);
    initMap = worldMap;

    //***********************  INIT HERO + PLAYER ****************************

    player.init();// position initial sur la map
    initHero();// remise à zero du hero
    this->setCurrentScene(worldMap);
}

MyGame::~MyGame()
{
    //dtor
    //  fermeture du programme déchargement des modules et sprites

    TTF_CloseFont(texteFont);
    TTF_CloseFont(menuFont);
    TTF_CloseFont(numberFont);

}

void MyGame::initHero()
{
    cout<<"initHero"<<endl;
    //  initilisation de perso et monstre
    //  pour les besoin de la demo
    Personnage* gobelin = new Personnage("Gobelin",100,20);
    Personnage* magicien = new Personnage("Magicien",90,30);
    Personnage* elisa = new Personnage("Elisa",110,10);

    gobelin->setCooldownMax(100);
    elisa->setCooldownMax(120);
    magicien->setCooldownMax(150);

    //  initalisation des capas ( [0] automatiqueme initiliser frape)
    magicien->setCapa(new Sort1,1);
    magicien->setCapa(new Sort2,2);
    magicien->setCapa(new Soin,3);
    magicien->setCapa(new MutiCible,4);

    //  initialisation des sprite perso
    gobelin->setsprite(IMG_Load("./data/sprite/gobelin.png"));
    magicien->setsprite(IMG_Load("./data/sprite/magicien.png"));
    elisa->setsprite(IMG_Load("./data/sprite/elisa.png"));

    //  création des groupes
    hero.addEntite(magicien,gobelin,elisa);// destruction des ancien heros gerées
}


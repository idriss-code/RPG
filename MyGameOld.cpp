#include "MyGame.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "fonction.h"
#include "constante.h"
#include "util/benrandom.h"
#include "menu/SousMenu.h"
#include "menuItem/Quit.h"
#include "menuItem/Continue.h"
#include "menuItem/AffichePerso.h"

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

#include "Scene/TestScene.h"

#include "Game.h"


//  variables globales

SDL_Window *ecran = NULL;//  chargé en variable globale pour simplifier la syntaxe

TTF_Font* numberFont=NULL;
TTF_Font* texteFont=NULL;
TTF_Font* menuFont=NULL;

Menu *mPrincipal=NULL;

Group hero;//???????  fusioner hero et player et incoporer initHero
Player player;
FinalMap* currentMap;

extern SDL_Color NOIR ;//  fonctionTTF.cpp
extern SDL_Color VERT ;

MyGame::MyGame()
{
    //ctor

    //*******************************  INIT SDL  **************************************************
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cerr<<"Unable to init SDL: %s\n"<< SDL_GetError()<<endl;
        exit(1);
    }

    TTF_Init(); // intialisation de SDL_TTF

    numberFont=TTF_OpenFont("data/Fette.ttf",15);
    texteFont=TTF_OpenFont("data/Augusta.ttf",20);
    menuFont=TTF_OpenFont("data/Fette.ttf",30);

     // intialisation de le SDL_MIXER

    Mix_Init(MIX_INIT_MP3);
    // start SDL with audio support
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        cerr<<"SDL_Init Audio: %s\n"<< SDL_GetError()<<endl;
        exit(1);
    }
    // open 44.1KHz, signed 16bit, system byte order,
    //      stereo audio, using 1024 byte chunks
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
        cerr<<"Mix_OpenAudio: %s\n"<< Mix_GetError()<<endl;
        exit(2);
    }

//****************************************  MENU  ************************************
    //  création du menu principal
    Menu MM(100,100,menuFont,19);//                             ????????????? à modifier
    mPrincipal=&MM;
    mPrincipal->addElement(new Continue("Continuer"));
    mPrincipal->addElement(new AffichePerso("Heros"));
    mPrincipal->addElement(new Quit("Quiter"));


// **************************************** INIT ECRAN cout<<"initGame"<<endl;****************************
    ecran = SDL_CreateWindow("Donjon Fantasy",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          WECRAN, HECRAN,
                          SDL_WINDOW_OPENGL);
//*********************************** CHARGEMENT MAP**********************************

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
    cout<<"fin game constr"<<endl;
}

MyGame::~MyGame()
{
    //dtor
    //  fermeture du programme déchargement des modules et sprites

    Mix_CloseAudio();
    while(Mix_Init(0))Mix_Quit();// force a quit

    TTF_CloseFont(texteFont);
    TTF_CloseFont(menuFont);
    TTF_CloseFont(numberFont);
    TTF_Quit();
    SDL_DestroyWindow(ecran);
    SDL_Quit();
}

void MyGame::main()
{

    while(this->status()!=QUIT){
        intro();
        // initialisation du game
        cout<<"initGame"<<endl;
        this->play();
        this->setCurrentScene(initMap);
        player.init();// position initial sur la map
        initHero();// remise à zero du hero
        while(this->status()==PLAY){
            cout<<"test"<<endl;
            this->currentScene()->exec();
        }
    }
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

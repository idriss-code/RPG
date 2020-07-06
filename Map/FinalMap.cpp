#include "FinalMap.h"
#include <iostream>
#include "../core/Game.h"
#include "../util/collision.h"
#include "../util/benrandom.h"
#include "../constante.h"
#include "../gfx/SDL2_rotozoom.h"
#include "../MapElement/Plan.h"
#include "../MapElement/Sortie.h"
#include "../Player.h"
#include "MenuScene.h"
#include "../Scene/combatScene.h"
extern Game* game;
//  position du hero sur la map(pas sur l'ecran)
extern Player player;

void FinalMap::load()
{
    vitesse=2;
    velx=0,vely=0;
    testDeplace=1;
    menu=0;
    action=0;
    WW =tileSet->w/tileWidth();
    hitBoxObstacle.x=0;
    hitBoxObstacle.y=0;
    hitBoxObstacle.w=tileWidth();
    hitBoxObstacle.h=tileHeight();
    //  sprite et hitbox du hero
    hitBox.w=player.width();
    hitBox.h=player.height();
    hitBox.x=SDL_GetWindowSurface(ecran)->w/2-player.width()/2;
    hitBox.y=SDL_GetWindowSurface(ecran)->h/2-player.height()/2;
    hitBoxTest=hitBox;//  servira aussi pour les deplacement et blit
    std::cerr<<"load map"<<std::endl;
}

void FinalMap::unload()
{
    std::cerr<<"unload map"<<std::endl;
}

void FinalMap::update(int dt)
{
        action=0;
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
                        menu=1;
                        break;
                    case SDLK_RIGHT:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        velx= vitesse;
                        break;
                    case SDLK_LEFT:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        velx= -vitesse;
                        break;
                    case SDLK_UP:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        vely= -vitesse;
                        break;
                    case SDLK_DOWN:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        vely= +vitesse;
                        break;
                    case SDLK_RETURN:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        action=1;
                        break;
                    default:
                        break;
                }
                case SDL_KEYUP:
                switch(event.key.keysym.sym)//  Gestion des touches du clavier
                {
                    case SDLK_RIGHT:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        velx= 0;
                        break;
                    case SDLK_LEFT:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        velx= 0;
                        break;
                    case SDLK_UP:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        vely= 0;
                        break;
                    case SDLK_DOWN:
                        event.key.keysym.sym=0;//evite les pb de repetition de touche
                        vely= 0;
                        break;
                    default:
                        break;
                }
                break;
        }

        if(menu){
            MenuScene::loach(this);
            menu=0;
        }

        /*test de collision obstacle */

        hitBoxTest=hitBox;
        hitBoxTest.x+=velx;
        hitBoxTest.y+=vely;
        testDeplace=1;
        for(int i=player.posX()/tileWidth()-1;i<player.posX()/tileWidth()+2;i++){
            for(int j=player.posY()/tileHeight()-1;j<player.posY()/tileHeight()+2;j++){
                if(mapElement[obj(i,j)]->isAWall()){
                    hitBoxObstacle.x=i*tileWidth()+SDL_GetWindowSurface(ecran)->w/2-player.posX();
                    hitBoxObstacle.y=j*tileHeight()+SDL_GetWindowSurface(ecran)->h/2-player.posY();
                    if(boxCollision(hitBoxTest,hitBoxObstacle))testDeplace=0;
                }
            }
        }

        /* deplacement si pas d'ocbstacle */

        if(testDeplace){
                if (player.deplace(velx,vely))combatAleatoire.incrStep();
        }

        if(combatAleatoire.testCombat()){
            //gestion du combat aléatoire
/*
            int i = combat(goupeDeMonstre[random(nbMonstre()-1)]);
            velx=vely=0;
            combatAleatoire.reset();
            if (i==RESET) {
                    loop=0;
            }
            */
            combatScene::loach(goupeDeMonstre[random(nbMonstre()-1)],this);
            velx=vely=0;
            combatAleatoire.reset();
        }else{
            //sinon test des event tuile de la map
                for(int i=player.posX()/tileWidth()-1;i<player.posX()/tileWidth()+2;i++){
                    for(int j=player.posY()/tileHeight()-1;j<player.posY()/tileHeight()+2;j++){
                        if(mapElement[obj(i,j)]->doActionOnEnter() || (mapElement[obj(i,j)]->doActionOnAction() && action)){
                            hitBoxObstacle.x=i*tileWidth()+SDL_GetWindowSurface(ecran)->w/2-player.posX();
                            hitBoxObstacle.y=j*tileHeight()+SDL_GetWindowSurface(ecran)->h/2-player.posY();
                                if(boxCollision(hitBox,hitBoxObstacle)){
                                        velx=vely=0;
                                        int test = mapElement[obj(i,j)]->action();
                                        if (test==RESET) {
                                            loop=0;
                                        }else if(test==EXIT_MAP){
                                            loop=0;
                                        }

                                }
                    }
                }
            }
        }
}

void FinalMap::draw()
{
        /* affichage de la map*/
            for(int i=player.posX()/tileWidth()-nbtuecranx/2-1; i<player.posX()/tileWidth()+nbtuecranx/2+2; i++){// affiche seulement ce qui est a l'ecran
                for(int j=player.posY()/tileHeight()-nbtuecrany/2-1; j<player.posY()/tileHeight()+nbtuecrany/2+2; j++){
 //               for(int i=0;i<width();i++){
 //                       for(int j=0;j<height();j++){
                    if (i>=0&&i< this->width()&&j>=0&&j< this->height()){

                        position.h=tileHeight();
                        source.h=tileHeight();
                        position.w=tileWidth();
                        source.w=tileWidth();

                        position.x=i*tileWidth()+SDL_GetWindowSurface(ecran)->w/2-player.posX();
                        position.y=j*tileHeight()+SDL_GetWindowSurface(ecran)->h/2-player.posY();

                        source.x = tile(i,j)%WW*tileWidth();
                        source.y = tile(i,j)/WW*tileHeight();

                        SDL_BlitSurface(tileSet,&source,SDL_GetWindowSurface(ecran),&position);
                    }
                }
            }

            //affichage sprite hero
            player.affiche(&hitBox);
}

FinalMap::FinalMap(const char* file,const char* TileSet,int Zoom): Map(file) ,m_nbMonstre(0),zoom(Zoom)
{
    //chargement du tileset et mise a l'echelle
        tileSet = IMG_Load(TileSet);
        SDL_Surface *temp = zoomSurface(tileSet,zoom,zoom,SMOOTHING_OFF);
        SDL_FreeSurface(tileSet);
        tileSet = temp;
        m_tileWidth = tileWidth()*zoom;
        m_tileHeight = tileHeight()*zoom;
    //calcul du nombre de tuile pas écran (écran doit etre initilisé)
        nbtuecranx=WECRAN/tileWidth();
        nbtuecrany=HECRAN/tileHeight();
    // valeur par default des objet tuile
        MapElement* tempEl = new Plan;
        for(int i=0;i<100;i++){mapElement[i]=tempEl;}
    // remise à zéro des combat aléatoire
        combatAleatoire.reset();
}

FinalMap::~FinalMap()
{
    //dtor
    SDL_FreeSurface(tileSet);
}

//
void setTunnel(FinalMap *map1,int obj1,FinalMap* map2,int obj2)
{
    int x1(0),x2(0),y1(0),y2(0);
    for(int i = 0;i<map1->width();i++){
            for(int j = 0;j<map1->height();j++){
                if (map1->obj(i,j)==obj1){
                    x1=i;
                    y1=j;
                }
            }
    }
    for(int i = 0;i<map2->width();i++){
            for(int j = 0;j<map2->height();j++){
                if (map2->obj(i,j)==obj2){
                    x2=i;
                    y2=j;
                }
            }
    }
    y1+=2;
    y2+=2;
    map1->addElement(new Sortie(map2,x2*map2->tileWidth()+map2->tileWidth()/2,y2*map2->tileHeight()),obj1);
    map2->addElement(new Sortie(map1,x1*map1->tileWidth()+map1->tileWidth()/2,y1*map1->tileHeight()),obj2);
}

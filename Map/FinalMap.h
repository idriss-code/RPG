#ifndef FINALMAP_H
#define FINALMAP_H

#include "Map.h"
#include "CombatAleatoire.h"
#include "../core/Scene.h"
#include <SDL.h>
#include <SDL_image.h>

class MapElement;
class Group;

class FinalMap : public Map, public Scene
{
    public:

        FinalMap(const char* file,const char* TileSet,int Zoom=2);
        virtual ~FinalMap();
        void addElement(MapElement* val,int position){mapElement[position]=val;}
        int nbMonstre() const {return m_nbMonstre;}
        void addMonstre(Group *val){goupeDeMonstre[m_nbMonstre++]=val;}
        virtual void draw();

    protected:
        virtual void load();
        virtual void unload();
        virtual void update(int dt);


    private:
        FinalMap();
        CombatAleatoire combatAleatoire;
        SDL_Surface* tileSet;

        int nbtuecranx;//=WECRAN/WTUILE;
        int nbtuecrany;//=HECRAN/HTUILE;

        MapElement* mapElement[100];

        Group *goupeDeMonstre[100];
        int m_nbMonstre;
        int zoom;



        int vitesse;
        int velx,vely;
        int testDeplace;
        int menu;
        int action;
        int WW;
        SDL_Rect position,source,hitBoxObstacle,hitBox,hitBoxTest;;


};

void setTunnel(FinalMap *map1,int obj1,FinalMap* map2,int obj2);

#endif // FINALMAP_H

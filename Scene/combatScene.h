#ifndef COMBATSCENE_H
#define COMBATSCENE_H

#include "../core/Scene.h"
#include "../constante.h"
#include "../Group.h"

class Group;
class Barre;
class combatScene : public Scene
{
    public:
        combatScene(Group *monstre,Scene* parent = NULL);
        virtual ~combatScene();
        virtual void draw();

        static void loach(Group *monstre,Scene* parent = NULL);

    protected:
        virtual void load();
        virtual void unload();
        virtual void update(int dt);
    private:
        Barre *barreCool[NBGRP];
        Group & monstre;
        SDL_Surface *selection;
        int returnVal;
        int timerFin;
        int menu;//  position dans le menu
        int selectHero,selectCapa,cible,groupecible;//  selectHero= hero selectioner / selectCapa= sort séléctioner / cible séléctioner
        Group groupe[2];

};

#endif // COMBATSCENE_H

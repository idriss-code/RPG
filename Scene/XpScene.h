#ifndef XPSCENE_H
#define XPSCENE_H

#include "../core/Scene.h"
#include "../Group.h"
#include "../constante.h"
#include "../util/Barre.h"

class XpScene : public Scene
{
    public:
        XpScene(Group* Monstre,Scene* parent = NULL);
        virtual ~XpScene();
        virtual void draw();

        static void loach(Group* Monstre,Scene* parent = NULL);

    protected:
        virtual void load();
        virtual void unload();
        virtual void update(int dt);
    private:
        int xpTotal;
        int xp[NBGRP];
        int xpS[NBGRP];
        int lvlUp[NBGRP];
        Group* monstre;
        Barre *barreCool[NBGRP];
        int delay;
        int delayInit;
};

#endif // XPSCENE_H

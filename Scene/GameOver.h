#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "../core/Scene.h"


class GameOver : public Scene
{
    public:
        GameOver(Scene* parent = NULL);
        virtual ~GameOver();

        static void loach(Scene* parent = NULL);
        virtual void draw();
        void clean();

    protected:
        virtual void load();
        virtual void unload();
        virtual void update(int dt);

    private:
};

#endif // GAMEOVER_H

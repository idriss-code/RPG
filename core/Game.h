#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "../constante.h"

class Game
{
    public:
        Game();
        void initSDL();// dans constructeur
        virtual ~Game();

        void main();

        int status(){return m_status;}

        void quit(){m_status=QUIT;}
        void reset(){m_status=RESET;}
        void play(){m_status=PLAY;}

        Scene* currentScene(){return m_currentScene;}
        void setCurrentScene(Scene* scene){m_currentScene=scene;}

    protected:

        int m_status;
        Scene* m_currentScene;

    private:
};

#endif // GAME_H

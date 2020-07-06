#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>

class Player
{
    public:
        Player();
        virtual ~Player();

        void affiche(SDL_Rect *hitBox);
        bool deplace(int velX, int velY);

        void setPosition(int x,int y){m_posX=x;m_posY=y;}
        int posX(){return m_posX;}
        int posY(){return m_posY;}
        int width(){return m_width;}
        int height(){return m_height;}

        void  init();
    protected:

    private:
        //SDL_Surface *sprite(){return m_sprite;}
        SDL_Surface *m_sprite;
        int m_posX;
        int m_posY;
        int m_width;
        int m_height;
        SDL_Rect source;

};

#endif // PLAYER_H

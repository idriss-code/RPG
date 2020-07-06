#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "Entite.h"

//  personnage hérite de entite

class Personnage : public Entite
{
    public:
        Personnage(const char*n,int pv=100,int mp=0);
        virtual ~Personnage();

        SDL_Surface *sprite(){return m_sprite;}
        void setsprite(SDL_Surface *sprite){m_sprite=sprite;}
        virtual void mort(){};

        int lvl() { return m_lvl; }
        int xp() { return m_xp; }
        int xpLvlSuivant(){return m_xpLvlSuivant;}

        int gainXp(int val);
        virtual void lvlUp();

        void reset();
        void afficheInitPos();
        void afficheMenu(SDL_Rect position);
    protected:
        SDL_Surface *m_sprite;

        int m_lvl;
        int m_xp;
        int m_xpLvlSuivant;

    private:

};

#endif // PERSONNAGE_H

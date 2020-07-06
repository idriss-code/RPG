#ifndef IABASIC_H
#define IABASIC_H

#include "../Monstre.h"


class IAbasic : public Monstre
{
    public:
        IAbasic(const char*n,int pv=100,int mp=0,int xp=10);
        virtual ~IAbasic();
        void comportement(Group &attaquant,Group &defense);
        virtual SDL_Surface *sprite()=0;

    protected:

    private:
};

#endif // IABASIC_H

#ifndef SOIN_H
#define SOIN_H

#include "../Capa.h"


class Soin : public Capa
{
    public:
        Soin();
        virtual ~Soin();
        void update(Entite &attaquant,Group &group,int cible);
        void draw();
    protected:

    private:
        int atqX;
        int atqY;
        int defX;
        int defY;
        int timer;
};

#endif // SOIN_H

#ifndef MUTICIBLE_H
#define MUTICIBLE_H

#include "../Capa.h"


class MutiCible : public Capa
{
    public:
        MutiCible();
        virtual ~MutiCible();
        void update(Entite &attaquant,Group &group,int cible);
        void draw();
    protected:

    private:
};

#endif // MUTICIBLE_H

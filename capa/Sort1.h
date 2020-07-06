#ifndef SORT1_H
#define SORT1_H

#include "../Capa.h"


class Sort1 : public Capa
{
    public:
        Sort1();
        virtual ~Sort1();
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

#endif // SORT1_H

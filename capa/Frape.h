#ifndef FRAPE_H
#define FRAPE_H
#include "../Entite.h"
#include "../Capa.h"


class Frape : public Capa
{
    public:
        Frape();
        virtual ~Frape();
        void update(Entite &attaquant,Group &group,int cible);
        void draw();
    protected:

    private:
};

#endif // FRAPE_H

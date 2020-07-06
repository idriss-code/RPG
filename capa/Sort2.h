#ifndef SORT2_H
#define SORT2_H

#include "../Capa.h"
#include "../Group.h"


class Sort2 : public Capa
{
    public:
        Sort2();
        virtual ~Sort2();
        void update(Entite &attaquant,Group &group,int cible);
        void draw();
    protected:


    private:
        static SDL_Surface *sprite;
        static int counter;
        SDL_Rect position;
        bool drawSprite;
};

#endif // SORT2_H

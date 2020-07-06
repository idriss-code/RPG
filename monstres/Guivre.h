#ifndef GUIVRE_H
#define GUIVRE_H

#include "IAbasic.h"


class Guivre : public IAbasic
{
    public:
        Guivre();
        virtual ~Guivre();

        SDL_Surface *sprite(){return m_sprite;}


    protected:

        static SDL_Surface *m_sprite;

    private:
        static int counter;
};

#endif // GUIVRE_H

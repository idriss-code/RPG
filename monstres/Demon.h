#ifndef DEMON_H
#define DEMON_H

#include "IAbasic.h"


class Demon : public IAbasic
{
    public:
        Demon();
        virtual ~Demon();

        SDL_Surface *sprite(){return m_sprite;}


    protected:

        static SDL_Surface *m_sprite;

    private:
        static int counter;
};

#endif // DEMON_H

#ifndef DRAGON_H
#define DRAGON_H

#include "IAbasic.h"


class Dragon : public IAbasic
{
    public:
        Dragon();
        virtual ~Dragon();

        SDL_Surface *sprite(){return m_sprite;}


    protected:

        static SDL_Surface *m_sprite;

    private:
        static int counter;
};

#endif // DRAGON_H

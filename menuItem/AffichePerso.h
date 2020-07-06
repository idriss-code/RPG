#ifndef AFFICHEPERSOITEM_H
#define AFFICHEPERSOITEM_H

#include "../menu/ElementMenu.h"
#include "../constante.h"


class AffichePerso :public ElementMenu
{
    public:
        AffichePerso(const char* name);

        virtual ~AffichePerso();

        int action(int val=0);



    protected:

    private:


};

#endif // AFFICHEPERSOITEM_H

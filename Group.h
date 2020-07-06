#ifndef GROUP_H_INCLUDED
#define GROUP_H_INCLUDED

#include "Entite.h"


//  groupe de monstre ou de hero
//  ???  devra contenir la gestion du groupe sur la map et la world map

class Entite;
class Group
{
    public:

        Group(Entite *h1=NULL,Entite *h2=NULL,Entite *h3=NULL,Entite *h4=NULL);
        ~Group();

        Entite * &operator[](int val){return entite[val];}

        void addEntite(Entite *h1,Entite *h2=NULL,Entite *h3=NULL,Entite *h4=NULL);

    private:
        Entite *entite[4];

};

#endif // GROUP_H_INCLUDED

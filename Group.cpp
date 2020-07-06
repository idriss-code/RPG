#include "Group.h"

Group::Group(Entite *h1,Entite *h2,Entite *h3,Entite *h4)
{
    entite[0]=h1;
    entite[1]=h2;
    entite[2]=h3;
    entite[3]=h4;

}
Group::~Group()
{
}

void Group::addEntite(Entite *h1,Entite *h2,Entite *h3,Entite *h4)
{

    for(int i=0;i<4;i++){
        if(entite[i])delete entite[i];
    }
    entite[0]=h1;
    entite[1]=h2;
    entite[2]=h3;
    entite[3]=h4;
}

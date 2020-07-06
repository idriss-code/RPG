#ifndef CAPA_H_INCLUDED
#define CAPA_H_INCLUDED

#include <SDL.h>
#include "constante.h"

#include "util/fonctionDessin.h"

enum{MULTI,UNIQUE};


class Group;
class Entite;
class Capa
{

        int m_cible;//  numero cible
        int m_groupe;//  groupe cible
        int m_mana;//  cout en mana
        char m_name[20];//  nom du sort

    public:
        Capa();
        virtual ~Capa();
        char* name(){return m_name;}
        void setName(const char*n);

        void setmultiple(){m_cible=MULTI;}
        void setgroupe(int grp){m_groupe=grp;}
        int groupecible(){return m_groupe;}
        int cible()const{return m_cible;}
        void setMana(int val){m_mana=val;}
        int mana()const{return m_mana;}

        virtual void update(Entite &attaquant,Group &group,int cible) =0;
        virtual void draw()=0;

        //int (*capa)(Entite &attaquant,Group &group,int cible);//  pointeur vers la fonction qui executera la capa
                                                            //  ??????????????  créé des sous objet qui contiendrons directement les fonctions sous la form operator()

};

#endif // CAPA_H_INCLUDED

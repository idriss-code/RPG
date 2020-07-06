#ifndef Entite_H
#define Entite_H
#include <SDL.h>
#include "Capa.h"
#include "util/fonctionTTF.h"

extern SDL_Window *ecran;
extern SDL_Color NOIR ;//  fonctionTTF.cpp
extern SDL_Color VERT ;


class Group;
class Entite
{
    public:
        Entite(const char*nom,int pv=100,int mp=0);
        virtual ~Entite();

        char*nom(){return m_nom;}
        void setnom(const char*n);
        int PV() { return m_PV; }
        int PVMax() { return m_PVMax; }
        void SetPVMax(unsigned int val) { m_PVMax = val; }
        int MP() { return m_MP; }
        int MPMax() { return m_MPMax; }
        void SetMPMax(unsigned int val) { m_MPMax = val; }

        void gainPV(unsigned int val);//  fonction affichage comprise
        void loosePV(unsigned int val);//  fonction affichage comprise

        void GainMP(unsigned int val) { m_MP += val;if (m_MP>m_MPMax)m_MP=m_MPMax; }
        void looseMP(unsigned int val) { m_MP -= val;if (m_MP<0)m_MP=0; }

        SDL_Rect &position(){return m_position;}// position courante du sprite
        SDL_Rect &positionInit(){return m_positionInit;}// position initial du sprite en debut de combat

        int anim(){return m_anim;}//???????
        void setAnim(int a){m_anim=a;}//?????????

        int &cooldown(){return m_cooldown;}
        int &cooldownMax(){return m_cooldownMax;}
        void setCooldownMax(int val){m_cooldownMax=val;}



        void setCapaActive(int c){m_capaActive=c;};
        int capaActive(){return m_capaActive;};

        int cible(){return m_cible;};
        void setcible(int c){m_cible=c;}
        Group *grpcible(){return m_grpcible;}
        void setgrpcible(Group *g){m_grpcible=g;}

        virtual void reset()=0;//debut combat
        virtual void mort()=0;// anim de mort

        virtual SDL_Surface *sprite()=0;
        //fonction affichage
        void afficheDegats(TTF_Font *police);
        void afficheSoin(TTF_Font *police);
        void afficheSprite();
        virtual void affichePV_MP(TTF_Font *police);

        int force(){return m_force;}
        int magie(){return m_magie;}
        int defPhys(){return m_defPhys;}
        int defMag(){return m_defMag;}

        int resist(int val){return m_resist[val];}

        void degat(Entite *cible, int element=PHYS, bool magie = false,int puissance=11);//  sert de base au capa
        void soin(Entite *cible,int puissance=10);// idem

        void setCapa(Capa* val,int i){m_capa[i]=val;}
        Capa* capa(int i){return m_capa[i];}

    protected:

        Capa *m_capa[NBCAPA];// tableau de cacite

        char m_nom[10];
        SDL_Rect m_position;
        SDL_Rect m_positionInit;

        int m_degatRecu;//  pour affichage
        int m_soinRecu;//  pour affichage
        unsigned int m_timer;//degat recu pour affichage

        int m_anim;//  0 si perso pret
        int m_cooldown;
        int m_cooldownMax;

        int m_PV;
        int m_PVMax;
        int m_MP;
        int m_MPMax;

        int m_capaActive;
        int m_cible;//
        Group *m_grpcible;// groupe cible (pour soin)

        int m_transparence;// pour mort

        int m_force;
        int m_magie;
        int m_defPhys;
        int m_defMag;

        int m_resist[NB_ELEMENTS];


};

#endif // Entite_H

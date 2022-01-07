#include "Entite.h"
#include "capa/Frape.h"
#include <cstdio>

Entite::Entite(const char*nom,int pv,int mp):m_degatRecu(0),m_soinRecu(0),m_timer(0),m_anim(0),m_transparence(255),m_force(1),m_magie(1),m_defPhys (1),m_defMag(1)


{
    //ctor

        m_capa[0]= new Frape;
        for(int i=1;i<NBCAPA;i++){
                m_capa[i]=0;
        }
        for(int i=0;i<NB_ELEMENTS;i++){
            m_resist[i]=NORMAL;
        }
        sprintf(m_nom,nom);
        m_PV=m_PVMax=pv;
        m_MP=m_MPMax=mp;
}

Entite::~Entite()
{
            //  liber le sprite ??? voir si pas de pb pour les monstre en plusieur exemplaire
    for(int i=1;i<NBCAPA;i++){
                delete m_capa[i];
        }
    //dtor
}

 void Entite::gainPV(unsigned int val)
  {
      m_PV += val;
      m_soinRecu=val;
      if (m_PV>m_PVMax)m_PV=m_PVMax;

   }
void Entite::loosePV(unsigned int val)
 {
     m_PV -= val;
     m_degatRecu=val;
    if (m_PV<0)m_PV=0;
 }
void Entite::afficheSprite(){
    if (m_transparence<=255){
            SDL_SetSurfaceAlphaMod(this->sprite(),m_transparence);
            SDL_UpperBlit(this->sprite(),NULL,SDL_GetWindowSurface(ecran),&this->position());
            SDL_SetSurfaceAlphaMod(this->sprite(),m_transparence);

    }else{
        SDL_UpperBlit(this->sprite(),NULL,SDL_GetWindowSurface(ecran),&this->position());
    }
}

//  affichage des PV perdu quand touch�
void Entite::afficheDegats(TTF_Font *police)
 {
            if(m_degatRecu)
            {
                static SDL_Rect position;
                position.x=m_position.x;
                position.y=m_position.y-10;
                afficheInt(position,m_degatRecu,ecran,police,NOIR);
                m_timer++;
                if (m_timer>30)m_degatRecu=0,m_timer=0;
            }
 }

//  affichage des PV perdu quand touch�
void Entite::afficheSoin(TTF_Font *police)
{
     if(m_soinRecu){
                static SDL_Rect position;
                position.x=m_position.x;
                position.y=m_position.y-10;
                afficheInt(position,m_soinRecu,ecran,police,VERT);
                m_timer++;
                if (m_timer>30)m_soinRecu=0,m_timer=0;}
}

void Entite::affichePV_MP(TTF_Font *police)
{

            static SDL_Rect position;
            //  affichage PV
            position.x=m_position.x+(sprite()->w/2)-20;
            position.y=m_position.y+sprite()->h;
            afficheIntSurInt(position,m_PV,m_PVMax,ecran,police,NOIR);
            //  affichage MP
            position.y+=15;
            afficheIntSurInt(position,m_MP,m_MPMax,ecran,police,NOIR);
            //  afffichage d�gat et soin
}

void Entite::degat(Entite *cible, int element, bool magie,int puissance)
{
    int DEGAT;
    if (!magie){
    DEGAT = (m_force*puissance - cible->m_defPhys)*cible->m_resist[element]/2;
    }else{
    DEGAT = (m_magie*puissance - cible->m_defMag)*cible->m_resist[element]/2;
    }
    if (DEGAT <0) cible->gainPV(-DEGAT);
    else cible->loosePV(DEGAT) ;
}

void Entite::soin(Entite *cible,int puissance)
{
    cible->gainPV(m_magie*puissance);
}
void Entite::setnom(const char*n){
    sprintf(m_nom,n);
}

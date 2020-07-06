#ifndef CONSTANTE_H_INCLUDED
#define CONSTANTE_H_INCLUDED

//  contante Nombre entite par groupe max
const int NBGRP=4;
const int NBCAPA = 5;
const int DIST_HERO=50;


enum cible{HERO,MONSTRE,PERSO,SORT,CIBLE,LOCK};

enum {QUIT,RESET,PLAY,MENU,EXIT_MAP};

const int NB_ELEMENTS=5;
enum elements{PHYS,FEU,EAU,TERRE,AIR};
enum resistElement{SENSIBL=4,NORMAL=2,DEMI=1,IMMUN=0,ABSORB=-1};



// taille de l'ecran
const int HECRAN=600;
const int WECRAN=800;

// coeff multiplacateur de xp par niveau
const int XP_LVL=27;




#endif // CONSTANTE_H_INCLUDED

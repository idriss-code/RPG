#include "Frape.h"
#include "../Group.h"

Frape::Frape()
{
    setName("attack");
    //ctor
}

Frape::~Frape()
{
    //dtor
}

void Frape::update(Entite &attaquant,Group &group,int cible)
{
        int v=10;//  vitesse de déplacement

        //  debut animation et vérif si perso dispo
        if (attaquant.anim()==1)
        {
            attaquant.setAnim(2);
            attaquant.cooldown()=attaquant.cooldownMax();
        }

        //  animation 1 allé vers ENI
        if (attaquant.anim()==2)
            {
                attaquant.position()=Trajectoire
                (attaquant.position().x,attaquant.position().y,group[cible]->position().x,group[cible]->position().y,v);

                if (attaquant.position().x==group[cible]->position().x
                    &&attaquant.position().y==group[cible]->position().y)attaquant.setAnim(3),attaquant.degat(group[cible]);/* arriver sur ENI passge anime 2 et perte de PV
                                                                                                                perte de PV fixer a 10 temporairement */

            }
        //  animation 2 retour
        else if(attaquant.anim()==3)
            {
                attaquant.position()=Trajectoire
                (attaquant.position().x,attaquant.position().y,attaquant.positionInit().x,attaquant.positionInit().y,v);
                if (attaquant.position().x==attaquant.positionInit().x&&
                    attaquant.position().y==attaquant.positionInit().y){attaquant.setAnim(0);}//  fin retour  perso pret

            }
}

void Frape::draw()
{

}

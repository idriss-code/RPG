#include "Boss.h"
#include "../constante.h"
#include "../Group.h"
#include "../Scene/combatScene.h"

Boss::Boss(Group* boss):theBoss(boss),isAlive(true)
{

}


Boss::~Boss()
{
    //dtor
    delete theBoss;
}

int Boss::action()
{
    if(isAlive){
        isAlive = false;
        combatScene::loach(theBoss,NULL);
        return PLAY;
    }else{
        return QUIT;
    }

}

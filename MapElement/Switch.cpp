#include "Switch.h"
#include "../constante.h"
#include "../Map/FinalMap.h"


Switch::Switch():x(0),y(0),newTile(0),newObj(0),oldTile(0),oldObj(0),actived(false)
{
    //ctor
}
Switch::Switch(FinalMap* Map,int X,int Y,int NewTile,int NewObj):oldTile(0),oldObj(0),actived(false)
{
    //ctor
    m_map=Map;x=X;y=Y;newObj=NewObj;newTile=NewTile;
    if(m_map){
        oldObj=m_map->obj(x,y);
        oldTile=m_map->tile(x,y);
    }

}
Switch::~Switch()
{
    //dtor
}

int Switch::action()
{
    if(!actived){
        m_map->setTile(x,y,newTile);
        m_map->setObj(x,y,newObj);
        actived=true;
    }else{
        m_map->setTile(x,y,oldTile);
        m_map->setObj(x,y,oldObj);
        actived=false;
    }

    return PLAY;
}

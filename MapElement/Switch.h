#ifndef SWITCH_H
#define SWITCH_H

#include "MapElement.h"

class FinalMap;
class Switch : public MapElement
{
    public:
        Switch();
        Switch(FinalMap* Map,int X,int Y,int NewTile,int NewObj);
        virtual ~Switch();

        void setChange(FinalMap* Map,int X,int Y,int NewTile,int NewObj){m_map=Map;x=X;y=Y;newObj=NewObj;newTile=NewTile;}

        virtual bool isAWall() const {return false;}
        virtual bool doActionOnEnter() const {return false;}
        virtual bool doActionOnAction() const {return true;}
        virtual bool isACombatZone() const {return false;}

        virtual int action();

    protected:

    private:
        int x,y,newTile,newObj,oldTile,oldObj;
        bool actived;
        FinalMap* m_map;


};

#endif // SWITCH_H

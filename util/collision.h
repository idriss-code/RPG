#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include <SDL.h>

bool pointCollision(int x,int y,SDL_Rect box);
bool boxCollision(SDL_Rect box1,SDL_Rect box2);


#endif // COLLISION_H_INCLUDED

#include "collision.h"

bool pointCollision(int x,int y,SDL_Rect box){
    if (x >= box.x
    && x < box.x + box.w
    && y >= box.y
    && y < box.y + box.h)
       return true;
   else
       return false;
}
bool boxCollision(SDL_Rect box1,SDL_Rect box2){
   if((box2.x >= box1.x + box1.w)      // trop à droite
    || (box2.x + box2.w <= box1.x) // trop à gauche
    || (box2.y >= box1.y + box1.h) // trop en bas
    || (box2.y + box2.h <= box1.y))  // trop en haut
          return false;
   else
          return true;
}

#ifndef BORDER_ENTITY_H
#define BORDER_ENTITY_H

#include "GameEntity.h"

// this is the parent class for hittable entities in the game, which are walls
// and the target
class HittableEntity : public GameEntity {
 protected:
  // this bool defines whether the entity has been hit by the light beam or not
  bool isHit;

 public:
  bool getHit() { return isHit; }
  // the children class implement what happens when they are hit
  virtual void hit() = 0;
};

#endif
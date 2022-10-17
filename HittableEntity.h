#ifndef BORDER_ENTITY_H
#define BORDER_ENTITY_H

#include "GameEntity.h"

// this is the parent class for entities in the game that can be hit by light
class HittableEntity : public GameEntity {
 protected:
  // includes a variable that stores whether the entity has been hit by light
  bool isHit;

 public:
  bool getHit() { return isHit; }
  // all children must implement what happens when they are hit by light
  virtual void hit() = 0;
};

#endif
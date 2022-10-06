#ifndef BORDER_ENTITY_H
#define BORDER_ENTITY_H

#include "GameEntity.h"

class BorderEntity : public GameEntity {
 protected:
    bool isHit;
 public:
    bool getHit() { return isHit; }
    virtual void hit() = 0;
    
};

#endif
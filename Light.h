#ifndef LIGHT_H
#define LIGHT_H

#include "Antitarget.h"
#include "GameEntity.h"
#include "Level.h"
#include "Mirror.h"
#include "Player.h"
#include "Target.h"
#include "Wall.h"

// this is the class for the light particles in the game
class Light : public GameEntity {
 private:
  Vector2f velocity;

 public:
  // constructor sets position and determines velocity for next particle
  Light(Vector2f previousPos, Vector2f previousVelocity, Mirror** mirrors,
        GameEntity* player, int winSize, int numOfMirrors, Wall** walls,
        int numOfWalls, HittableEntity* target, Antitarget** antitargets,
        int numOfAntiTargets) {
    body = new sf::RectangleShape(Vector2f(64, 64));
    velocity = previousVelocity;
    body->setPosition(previousPos + velocity);
    body->setFillColor(sf::Color::Cyan);

    // stop light if hits border
    if (body->getPosition().x == 0 || body->getPosition().y == 0 ||
        body->getPosition().x == winSize || body->getPosition().y == winSize) {
      velocity = Vector2f(0, 0);
    } 
    
    // determine velocity of next particle based on whether specific entities have been hit

    // stop light if player hit
    else if (body->getPosition().x == player->getPos().x &&
               body->getPosition().y == player->getPos().y) {
      velocity = Vector2f(0, 0);
    }
    
    // reflect light if mirror hit
    for (int i = 0; i < numOfMirrors; i++) {
      if (body->getPosition().x == mirrors[i]->getPos().x &&
          body->getPosition().y == mirrors[i]->getPos().y) {
        switch (mirrors[i]->getDirection()) {
          case 'N':
            if (velocity.y == 64) {
              velocity = Vector2f(64, 0);
            } else if (velocity.x == -64) {
              velocity = Vector2f(0, -64);
            } else {
              velocity = Vector2f(0, 0);
            }
            break;
          case 'E':
            if (velocity.x == -64) {
              velocity = Vector2f(0, 64);
            } else if (velocity.y == -64) {
              velocity = Vector2f(64, 0);
            } else {
              velocity = Vector2f(0, 0);
            }
            break;
          case 'S':
            if (velocity.y == -64) {
              velocity = Vector2f(-64, 0);
            } else if (velocity.x == 64) {
              velocity = Vector2f(0, 64);
            } else {
              velocity = Vector2f(0, 0);
            }
            break;
          case 'W':
            if (velocity.x == 64) {
              velocity = Vector2f(0, -64);
            } else if (velocity.y == 64) {
              velocity = Vector2f(-64, 0);
            } else {
              velocity = Vector2f(0, 0);
            }
            break;
        }
      }
    }

    // stop light if wall hit
    for (int i = 0; i < numOfWalls; i++) {
      if (body->getPosition().x == walls[i]->getPos().x &&
          body->getPosition().y == walls[i]->getPos().y) {
        velocity = Vector2f(0, 0);
        walls[i]->hit();
      }
    }

    // stop light if antitarget hit
    for (int i = 0; i < numOfAntiTargets; i++) {
      if (body->getPosition().x == antitargets[i]->getPos().x &&
          body->getPosition().y == antitargets[i]->getPos().y) {
        velocity = Vector2f(0, 0);
        antitargets[i]->hit();
      }
    }

    // stop light if target hit
    if (body->getPosition().x == target->getPos().x &&
        body->getPosition().y == target->getPos().y) {
      velocity = Vector2f(0, 0);
      target->hit();
    }
  }
  
  Vector2f getVelocity() { return velocity; }
};

#endif
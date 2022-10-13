#ifndef LIGHT_H
#define LIGHT_H

#include "GameEntity.h"
#include "Level.h"
#include "Mirror.h"
#include "Player.h"
#include "Wall.h"
#include "Target.h"

// this is the class for the light particles in the game
class Light : public GameEntity {
 private:
  Vector2f velocity;

 public:
  // when a new light particle is created determine velocity of next particle based on location
  Light(Vector2f previousPos, Vector2f previousVelocity, Mirror** mirrors,
        Player* player, int winSize, int numOfMirrors, Wall** walls, int numOfWalls, Target* target) {
    body = new sf::RectangleShape(Vector2f(64, 64));
    velocity = previousVelocity;

    // set position of light based on previous and velocitys
    body->setPosition(previousPos + velocity);
    body->setFillColor(sf::Color::Cyan);

    // stop if hits border or player
    if (body->getPosition().x == 0 || body->getPosition().y == 0 ||
        body->getPosition().x == winSize || body->getPosition().y == winSize) {
      velocity = Vector2f(0, 0);
    } else if (body->getPosition().x == player->getPos().x &&
               body->getPosition().y == player->getPos().y) {
      velocity = Vector2f(0, 0);
    }

    // reflect light if it hits a mirror
    for (int i = 0; i < numOfMirrors; i++) {
      if (body->getPosition().x == mirrors[i]->getPos().x &&
          body->getPosition().y == mirrors[i]->getPos().y) {
        switch (mirrors[i]->getDirection()) {
          // determine direction of light based on mirror direction
          case 'N':
            if (velocity.y == 64) {
              velocity = Vector2f(64, 0);
            } else if (velocity.x == -64, 0) {
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

    // stop light if hits wall
    for (int i = 0; i < numOfWalls; i++) {
      if (body->getPosition().x == walls[i]->getPos().x &&
          body->getPosition().y == walls[i]->getPos().y) {
            velocity = Vector2f(0, 0);
            walls[i]->hit();
          }
    }

    // stop if hits target
    if (body->getPosition().x == target->getPos().x &&
          body->getPosition().y == target->getPos().y) {
            velocity = Vector2f(0, 0);
            target->hit();
          }
  }

  Vector2f getPos() { return body->getPosition(); }
  Vector2f getVelocity() { return velocity; }
};

#endif
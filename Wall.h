#ifndef WALL_H
#define WALL_H

#include "BorderEntity.h"

class Wall : public BorderEntity {
    private:
        int x;
    public:
        Wall() {
            body = new RectangleShape(Vector2f(64, 64));
            body->setFillColor(sf::Color{125, 21, 19});
        }

        Wall(Vector2f initialPosition): Wall() {
            body->setPosition(initialPosition);
        }

        void hit() {
            isHit = true;
            body->setFillColor(sf::Color{201, 37, 34});
        }

        Vector2f getPos() { return body->getPosition(); }
};

#endif
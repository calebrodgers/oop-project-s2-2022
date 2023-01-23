#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include "Antitarget.h"
#include "BorderWall.h"
#include "Emitter.h"
#include "GameEntity.h"
#include "Light.h"
#include "Mirror.h"
#include "Player.h"
#include "Target.h"
#include "Wall.h"

// this is the class for the game's levels
class Level {
 private:
  sf::Clock clock;

  // number of game entities there are multiple of
  int numOfMirrors;
  int numOfWalls;
  int numOfAntitargets;
  int countLight;

  // determine whether game is done, reset
  bool done;
  bool reset;

  // pointers to all the entities in the level
  Mirror** mirrors;
  Player* player;
  BorderWall* border;
  Emitter* emitter;
  Target* target;
  std::vector<Light*> light;
  Wall** walls;
  Antitarget** antitargets;

 public:
  // constructor creates the level based on characters in the level layout file
  Level(std::string fileName, int levelIdx) {
    done = false;
    reset = false;
    // read in lines
    std::ifstream file(fileName);
    std::string lines[levelIdx * 12 + 12];
    for (int i = 0; i < levelIdx * 12 + 12; i++) {
      getline(file, lines[i]);
    }
    file.close();

    // count mirrors in level
    numOfMirrors = 0;
    for (int i = levelIdx * 12; i < levelIdx * 12 + 12; i++) {
      for (int j = 0; j < 12; j++) {
        if (lines[i][j] == 'N' || lines[i][j] == 'E' || lines[i][j] == 'S' ||
            lines[i][j] == 'W') {
          numOfMirrors++;
        }
      }
    }

    // count walls in level
    numOfWalls = 0;
    for (int i = levelIdx * 12; i < levelIdx * 12 + 12; i++) {
      for (int j = 0; j < 12; j++) {
        if (lines[i][j] == 'w') {
          numOfWalls++;
        }
      }
    }

    // count antitargets in level
    numOfAntitargets = 0;
    for (int i = levelIdx * 12; i < levelIdx * 12 + 12; i++) {
      for (int j = 0; j < 12; j++) {
        if (lines[i][j] == 'a') {
          numOfAntitargets++;
        }
      }
    }

    // create game objects based on character in level layout file
    int mirrorIdx = 0;
    mirrors = new Mirror*[numOfMirrors];

    int wallIdx = 0;
    walls = new Wall*[numOfWalls];

    int antiIdx = 0;
    antitargets = new Antitarget*[numOfAntitargets];

    for (int i = levelIdx * 12; i < levelIdx * 12 + 12; i++) {
      for (int j = 0; j < 12; j++) {
        // add mirrors
        if (lines[i][j] == 'N' || lines[i][j] == 'E' || lines[i][j] == 'S' ||
            lines[i][j] == 'W') {
          mirrors[mirrorIdx] = new Mirror(
              Vector2f(64 * j, 64 * (i - (levelIdx * 12))), lines[i][j]);
          mirrorIdx++;
        }

        // add player
        if (lines[i][j] == 'p') {
          player = new Player(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
        }

        // add target
        if (lines[i][j] == 'g') {
          target = new Target(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
        }

        // add emitter
        if (lines[i][j] == 'e') {
          emitter =
              new Emitter(Vector2f(64 * j, 64 * (i - (levelIdx * 12))), 704);
        }

        // add walls
        if (lines[i][j] == 'w') {
          walls[wallIdx] =
              new Wall(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
          wallIdx++;
        }

        // add antitarget
        if (lines[i][j] == 'a') {
          antitargets[antiIdx] =
              new Antitarget(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
          antiIdx++;
        }
      }
    }

    // create border wall around level
    border = new BorderWall(768);
  }

  // update elements in the level and draw entities
  void updateAndDraw(RenderWindow* window) {
    for (int i = 0; i < numOfWalls; i++) {
      walls[i]->notHit();
    }

    int lightMoving = true;

    // remove prevoius light particles
    for (int i = 0; i < light.size(); i++) {
      delete light[i];
    }
    light.clear();
    countLight = 0;

    // creating light particles
    while (lightMoving == true) {
      if (countLight == 0) {
        light.push_back(new Light(emitter->getPos(),
                                  emitter->getInitialVelocity(), mirrors,
                                  player, 768, numOfMirrors, walls, numOfWalls,
                                  target, antitargets, numOfAntitargets));
        if (light[countLight]->getVelocity() == Vector2f(0, 0)) {
          lightMoving = false;
        }
        countLight++;
      } else {
        light.push_back(new Light(light[countLight - 1]->getPos(),
                                  light[countLight - 1]->getVelocity(), mirrors,
                                  player, 768, numOfMirrors, walls, numOfWalls,
                                  target, antitargets, numOfAntitargets));
        if (light[countLight]->getVelocity() == Vector2f(0, 0)) {
          lightMoving = false;
        }
        countLight++;
      }
    }
    countLight = 0;

    // update player
    Vector2f old_pos = player->getPos();
    player->update(numOfMirrors, mirrors, walls, numOfWalls, antitargets,
                   numOfAntitargets);
    Vector2f current_pos = player->getPos();
    Vector2f direction;
    bool moved = false;

    if (current_pos != old_pos) {
      direction.x = old_pos.x - current_pos.x;
      direction.y = old_pos.y - current_pos.y;

      player->move(direction, 768, numOfMirrors, mirrors, walls, numOfWalls,
                   antitargets, numOfAntitargets);
      direction.x = direction.x / -16;
      direction.y = direction.y / -16;
      moved = true;
    }

    for (int frame = 0; frame < 16; frame++) {
      window->clear(sf::Color::White);
      // draw border
      border->draw(window);
      for (int row = 0; row <= 704; row = row + 64) {
        // draw mirrors base
        for (int i = 0; i < numOfMirrors; i++) {
          if (mirrors[i]->getPos().y == row) {
            mirrors[i]->drawBase(window);
          }
        }

        // draw light
        for (int i = 0; i < light.size() - 1; i++) {
          if (light[i]->getPos().y == row) {
            light[i]->draw(window);
          }
        }

        // draw mirrors
        for (int i = 0; i < numOfMirrors; i++) {
          if (mirrors[i]->getPos().y == row) {
            mirrors[i]->draw(window);
          }
        }

        // draw walls
        for (int i = 0; i < numOfWalls; i++) {
          if (walls[i]->getPos().y == row) {
            walls[i]->draw(window);
          }
        }

        // draw antitargets
        for (int i = 0; i < numOfAntitargets; i++) {
          if (antitargets[i]->getPos().y == row) {
            antitargets[i]->draw(window);
          }
        }

        // draw target and emitter
        if (target->getPos().y == row) {
          target->draw(window);
        }
        if (emitter->getPos().y == row) {
          emitter->draw(window);
        }

        // animate and draw player
        if (old_pos.y == row) {
          if (moved) {
            player->animate(direction);

            if (frame == 3) {
              player->spriteIncrement();
            }
            if (frame == 10) {
              player->spriteIncrement();
            }
          }

          player->draw(window);
        }
      }
      if (moved) {
        clock.restart();
        while (clock.getElapsedTime().asSeconds() < 0.01) {
        }
      }
      window->display();
    }
    moved = false;

    // reset level if antitarget hit
    for (int i = 0; i < numOfAntitargets; i++) {
      if (antitargets[i]->getHit()) {
        reset = true;
      }
    }

    // if target is hit finish level
    if (target->getHit()) {
      done = true;
    }
  }

  int getNumOfMirrors() { return numOfMirrors; }

  Mirror** getMirrors() { return mirrors; }

  Player* getPlayer() { return player; }

  bool isDone() { return done; }

  bool needsReset() { return reset; }

  // destructor deletes game entities
  ~Level() {
    // delete all light particles, mirrors, walls, antitargets
    for (int i = 0; i < light.size(); i++) {
      delete light[i];
    }

    for (int i = 0; i < numOfMirrors; i++) {
      delete mirrors[i];
    }

    for (int i = 0; i < numOfWalls; i++) {
      delete walls[i];
    }

    for (int i = 0; i < numOfAntitargets; i++) {
      delete antitargets[i];
    }

    // delete array for light, walls, mirrors, antitarget
    light.clear();
    delete[] mirrors;
    delete[] walls;
    delete[] antitargets;

    // delete other game entities
    delete player;
    delete target;
    delete border;
    delete emitter;
  }
};

#endif
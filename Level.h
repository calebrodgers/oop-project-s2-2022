#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <fstream>
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

class Level {
 private:
  int numOfMirrors;
  int numOfWalls;
  int numOfAntitargets;
  int countLight;
  bool done;
  bool reset;
  Mirror** mirrors;
  Player* player;
  BorderWall* border;
  Emitter* emitter;
  Target* target;
  std::vector<Light*> light;
  Wall** walls;
  Antitarget** antitargets;

 public:
  Level(std::string fileName, int levelIdx) {
    done = false;
    reset = false;
    // Read in lines
    std::ifstream file(fileName);
    std::string lines[levelIdx * 12 + 12];
    for (int i = 0; i < levelIdx * 12 + 12; i++) {
      getline(file, lines[i]);
    }
    file.close();

    // Count mirrors in level
    numOfMirrors = 0;
    for (int i = levelIdx * 12; i < levelIdx * 12 + 12; i++) {
      for (int j = 0; j < 12; j++) {
        if (lines[i][j] == 'N' || lines[i][j] == 'E' || lines[i][j] == 'S' ||
            lines[i][j] == 'W') {
          numOfMirrors++;
        }
      }
    }

    // Count walls in level
    numOfWalls = 0;
    for (int i = levelIdx * 12; i < levelIdx * 12 + 12; i++) {
      for (int j = 0; j < 12; j++) {
        if (lines[i][j] == 'w') {
          numOfWalls++;
        }
      }
    }

    // Count antitargets in level
    numOfAntitargets = 0;
    for (int i = levelIdx * 12; i < levelIdx * 12 + 12; i++) {
      for (int j = 0; j < 12; j++) {
        if (lines[i][j] == 'a') {
          numOfAntitargets++;
        }
      }
    }

    // Create game objects
    int mirrorIdx = 0;
    mirrors = new Mirror*[numOfMirrors];

    int wallIdx = 0;
    walls = new Wall*[numOfWalls];

    int antiIdx = 0;
    antitargets = new Antitarget*[numOfAntitargets];

    for (int i = levelIdx * 12; i < levelIdx * 12 + 12; i++) {
      for (int j = 0; j < 12; j++) {
        if (lines[i][j] == 'N' || lines[i][j] == 'E' || lines[i][j] == 'S' ||
            lines[i][j] == 'W') {
          mirrors[mirrorIdx] = new Mirror(
              Vector2f(64 * j, 64 * (i - (levelIdx * 12))), lines[i][j]);
          mirrorIdx++;
        }
        if (lines[i][j] == 'p') {
          player = new Player(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
        }
        if (lines[i][j] == 'g') {
          target = new Target(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
        }
        if (lines[i][j] == 'e') {
          emitter =
              new Emitter(Vector2f(64 * j, 64 * (i - (levelIdx * 12))), 704);
        }
        if (lines[i][j] == 'w') {
          walls[wallIdx] =
              new Wall(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
          wallIdx++;
        }
        if (lines[i][j] == 'a') {
          antitargets[antiIdx] =
              new Antitarget(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
          antiIdx++;
        }
      }
    }
    border = new BorderWall(768);
  }

  void updateAndDraw(RenderWindow* window) {
    for (int i = 0; i < numOfMirrors; i++) {
      mirrors[i]->drawBase(window);
    }

    int lightMoving = true;

    for (int i = 0; i < light.size(); i++) {
      delete light[i];
    }
    light.clear();
    countLight = 0;

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
    for (int i = 0; i < light.size() - 1; i++) {
      light[i]->draw(window);
    }
    countLight = 0;

    player->update(numOfMirrors, mirrors, walls, numOfWalls, antitargets,
                   numOfAntitargets);
    for (int i = 0; i < numOfMirrors; i++) {
      mirrors[i]->draw(window);
    }

    for (int i = 0; i < numOfWalls; i++) {
      walls[i]->draw(window);
    }

    border->draw(window);

    for (int i = 0; i < numOfAntitargets; i++) {
      antitargets[i]->draw(window);
    }

    target->draw(window);
    emitter->draw(window);
    player->draw(window);

    for (int i = 0; i < numOfAntitargets; i++) {
      if (antitargets[i]->getHit()) {
        reset = true;
      }
    }

    if (target->getHit()) {
      done = true;
    }
  }

  int getNumOfMirrors() { return numOfMirrors; }

  Mirror** getMirrors() { return mirrors; }

  Player* getPlayer() { return player; }

  bool isDone() { return done; }

  bool needsReset() { return reset; }

  ~Level() {
    delete player;
    delete[] mirrors;
    delete[] walls;
    delete target;
  }
};

#endif
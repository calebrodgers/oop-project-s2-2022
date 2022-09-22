#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <fstream>

#include "BorderWall.h"
#include "Emitter.h"
#include "GameEntity.h"
#include "Mirror.h"
#include "Player.h"
#include "Target.h"

class Level {
 private:
  int numOfMirrors;
  Mirror** mirrors;
  Player* player;
  BorderWall* border;
  Emitter* emitter;
  Target* target;

 public:
  Level(std::string fileName, int levelIdx) {
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
        if (lines[i][j] == 'm') {
          numOfMirrors++;
        }
      }
    }

    // Create game objects
    int mirrorIdx = 0;
    mirrors = new Mirror*[numOfMirrors];

    for (int i = levelIdx * 12; i < levelIdx * 12 + 12; i++) {
      for (int j = 0; j < 12; j++) {
        if (lines[i][j] == 'm') {
          mirrors[mirrorIdx] =
              new Mirror(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
          mirrorIdx++;
        }
        if (lines[i][j] == 'p') {
          player = new Player(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
        }
        if (lines[i][j] == 'g') {
          target = new Target(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
        }
        if (lines[i][j] == 'e') {
          emitter = new Emitter(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
        }
      }
    }
    border = new BorderWall(768);
  }

  void updateAndDraw(RenderWindow* window) {
    player->update(numOfMirrors, mirrors);
    for (int i = 0; i < numOfMirrors; i++) {
      mirrors[i]->draw(window);
    }

    player->draw(window);
    border->draw(window);
    target->draw(window);
    emitter->draw(window);
  }

  int getNumOfMirrors() { return numOfMirrors; }

  Mirror** getMirrors() { return mirrors; }

  Player* getPlayer() { return player; }

  ~Level() {
    delete player;
    delete[] mirrors;
  }
};

#endif
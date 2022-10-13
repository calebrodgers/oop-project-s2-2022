#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <fstream>

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
  // number of game entities there are multiple of
  int numOfMirrors;
  int numOfWalls;
  int countLight;

  // determines when the game is done
  bool done;

  // pointers to all the entities in the level
  Mirror** mirrors;
  Player* player;
  BorderWall* border;
  Emitter* emitter;
  Target* target;
  Light** light;
  Wall** walls;

 public:
  // Constructor creates the level based on characters in the levels.nrlvl file
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

    // Create game objects based on character in levels.nrlvl file
    int mirrorIdx = 0;
    mirrors = new Mirror*[numOfMirrors];

    int wallIdx = 0;
    walls = new Wall*[numOfWalls];

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

        // add light emitter
        if (lines[i][j] == 'e') {
          emitter =
              new Emitter(Vector2f(64 * j, 64 * (i - (levelIdx * 12))), 768);
        }

        // add walls
        if (lines[i][j] == 'w') {
          walls[wallIdx] = new Wall(Vector2f(64 * j, 64 * (i - (levelIdx * 12))));
          wallIdx++;
          
        }
      }
    }

    // create borderwall and light
    border = new BorderWall(768);
    light = new Light*[100];
  }


  // update elements in the level and draw entities
  void updateAndDraw(RenderWindow* window) {
    int lightMoving = true;
    countLight = 0;
    delete[] light;
    light = new Light*[100];

    // creating light particles
    while (lightMoving == true) {
      if (countLight == 0) {
        light[countLight] =
            new Light(emitter->getPos(), emitter->getInitialVelocity(), mirrors,
                      player, 768, numOfMirrors, walls, numOfWalls, target);
        if (light[countLight]->getVelocity() == Vector2f(0, 0)) {
          lightMoving = false;
        }
        countLight++;
      } else {
        light[countLight] = new Light(light[countLight - 1]->getPos(),
                                      light[countLight - 1]->getVelocity(),
                                      mirrors, player, 768, numOfMirrors, 
                                      walls, numOfWalls, target);
        if (light[countLight]->getVelocity() == Vector2f(0, 0)) {
          lightMoving = false;
        }
        countLight++;
      }
    }

    // draw light
    for (int i = 0; i < countLight; i++) {
      light[i]->draw(window);
    }
    countLight = 0;

    // update player
    player->update(numOfMirrors, mirrors, walls, numOfWalls);

    // draw game entities
    for (int i = 0; i < numOfMirrors; i++) {
      mirrors[i]->draw(window);
    }
    for (int i = 0; i < 1; i++) {
      walls[i]->draw(window);
    }
    player->draw(window);
    border->draw(window);
    target->draw(window);
    emitter->draw(window);

    // finish the level if the target has been hit
    if (target->getHit()) {
      done = true;
    }
    
  }

  int getNumOfMirrors() { return numOfMirrors; }

  Mirror** getMirrors() { return mirrors; }

  Player* getPlayer() { return player; }

  int getLightCount() { return countLight; }

  bool isDone() { return done; } 

  ~Level() {
    delete player;
    delete[] mirrors;
    delete[] walls;
  }
};

#endif
#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

// this is the class for the scorebord in the game
class Scoreboard {
 private:
  Font *font = new Font();
  Text *text = new Text();

 public:
  // constructor sets up text properties
  Scoreboard(Vector2f pos) {
    font->loadFromFile("assets/fonts/Silkscreen-Regular.ttf");
    text->setFont(*font);
    text->setString("NR");
    text->setPosition(pos);
    text->setCharacterSize(48);
  }

  // display text for the current level
  void updateAndDraw(int level, RenderWindow *window) {
    std::string levelString = "LEVEL: ";
    levelString.append(std::to_string(level));
    text->setString(levelString);
    window->draw(*text);
  }

  ~Scoreboard() {}
};
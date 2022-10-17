#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

// this is the class for cutscenes in the game
class Cutscene {
 private:
  sf::Clock clock;
  Font *font = new Font();
  Text *text = new Text();

 public:
  // constructor sets text properties and initializes position
  Cutscene(std::string message, bool levelComplete) {
    font->loadFromFile("assets/fonts/Silkscreen-Regular.ttf");
    text->setFont(*font);
    text->setCharacterSize(64);
    text->setString(message);
    sf::FloatRect textShape = text->getLocalBounds();
    text->setOrigin(textShape.left + textShape.width / 2.0f,
                    textShape.top + textShape.height / 2.0f);
    text->setPosition(sf::Vector2f(768 / 2.0f, 768 / 2.0f));

    // change color of text depending on whether it is showing after a level
    if (levelComplete) {
      text->setFillColor(sf::Color::Black);
    } else {
      text->setFillColor(sf::Color::White);
    }
  }

  // run function shows the text for appropriate amount of time
  void run(RenderWindow *window, bool levelComplete, bool preDelay) {
    clock.restart();

    // delay the text appearing for half a second
    if (preDelay) {
      while (clock.getElapsedTime().asSeconds() < 0.5) {
      }
    }
    clock.restart();

    // show text on screen for 1.5 seconds
    while (clock.getElapsedTime().asSeconds() < 1.5) {
      if (levelComplete) {
        window->clear(sf::Color::White);
      } else {
        window->clear(sf::Color::Black);
      }
      window->draw(*text);
      window->display();
    }
  }

  ~Cutscene(){};
};
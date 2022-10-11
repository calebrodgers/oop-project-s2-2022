#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class Cutscene {
 private:
  sf::Clock clock;
  Font *font = new Font();
  Text *text = new Text();

 public:
  Cutscene(int level, bool levelComplete, bool wasRPressed) {
    font->loadFromFile("assets/fonts/Silkscreen-Regular.ttf");
    text->setFont(*font);
    text->setCharacterSize(64);

    if (levelComplete) {
      text->setFillColor(sf::Color::Black);
      std::string levelString = "LEVEL ";
      levelString.append(std::to_string(level + 1));
      levelString.append(" COMPLETED");
      text->setString(levelString);
      sf::FloatRect textShape = text->getLocalBounds();
      text->setOrigin(textShape.left + textShape.width / 2.0f,
                      textShape.top + textShape.height / 2.0f);
      text->setPosition(sf::Vector2f(768 / 2.0f, 768 / 2.0f));
    } else if (!levelComplete && wasRPressed) {
      text->setFillColor(sf::Color::White);
      std::string levelString = "RESETTING LEVEL";
      text->setString(levelString);
      sf::FloatRect textShape = text->getLocalBounds();
      text->setOrigin(textShape.left + textShape.width / 2.0f,
                      textShape.top + textShape.height / 2.0f);
      text->setPosition(sf::Vector2f(768 / 2.0f, 768 / 2.0f));
    } else {
      text->setFillColor(sf::Color::White);
      std::string levelString = "LEVEL FAILED";
      text->setString(levelString);
      sf::FloatRect textShape = text->getLocalBounds();
      text->setOrigin(textShape.left + textShape.width / 2.0f,
                      textShape.top + textShape.height / 2.0f);
      text->setPosition(sf::Vector2f(768 / 2.0f, 768 / 2.0f));
    }
  }

  void run(RenderWindow *window, bool levelComplete) {
    clock.restart();
    while (clock.getElapsedTime().asSeconds() < 0.5) {
    }
    while (clock.getElapsedTime().asSeconds() < 2) {
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
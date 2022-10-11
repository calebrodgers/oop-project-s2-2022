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
  Cutscene(std::string message, bool levelComplete) {
    font->loadFromFile("assets/fonts/Silkscreen-Regular.ttf");
    text->setFont(*font);
    text->setCharacterSize(64);
    text->setString(message);
    sf::FloatRect textShape = text->getLocalBounds();
    text->setOrigin(textShape.left + textShape.width / 2.0f,
                    textShape.top + textShape.height / 2.0f);
    text->setPosition(sf::Vector2f(768 / 2.0f, 768 / 2.0f));

    if (levelComplete) {
      text->setFillColor(sf::Color::Black);
    } else {
      text->setFillColor(sf::Color::White);
    }
  }

  void run(RenderWindow *window, bool levelComplete, bool preDelay) {
    clock.restart();
    if (preDelay) {
      while (clock.getElapsedTime().asSeconds() < 0.5) {
      }
    }
    clock.restart();
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
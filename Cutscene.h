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
  Cutscene(int prevLevel) {
    font->loadFromFile("assets/fonts/Silkscreen-Regular.ttf");
    text->setFont(*font);
    text->setFillColor(sf::Color::Black);
    text->setCharacterSize(64);

    std::string levelString = "LEVEL ";
    levelString.append(std::to_string(prevLevel + 1));
    levelString.append(" COMPLETED");
    text->setString(levelString);
    sf::FloatRect textShape = text->getLocalBounds();
    text->setOrigin(textShape.left + textShape.width / 2.0f,
                    textShape.top + textShape.height / 2.0f);
    text->setPosition(sf::Vector2f(768 / 2.0f, 768 / 2.0f));
  }

  void run(RenderWindow *window) {
    clock.restart();
    while (clock.getElapsedTime().asSeconds() < 0.5) {
    }
    while (clock.getElapsedTime().asSeconds() < 2) {
      window->clear(sf::Color::White);
      window->draw(*text);
      window->display();
    }
  }

  ~Cutscene(){};
};
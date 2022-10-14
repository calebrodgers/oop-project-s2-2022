#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class TutorialText {
 private:
  sf::Clock clock;
  Font *font = new Font();
  Text *text = new Text();

 public:
  TutorialText(RenderWindow *window, int levelNum, int loopCount) {
    font->loadFromFile("assets/fonts/Silkscreen-Regular.ttf");
    text->setFont(*font);
    text->setCharacterSize(32);
    text->setFillColor(Color::Black);

    if (levelNum == 0) {
      if (loopCount == 0) {
        text->setCharacterSize(64);

        waitAndPrint(window, 0, "Welcome to", Vector2f(70, 364));

        waitAndPrint(window, 2, ". . .", Vector2f(70, 434));
      }

      if (loopCount == 1) {
        text->setCharacterSize(64);

        waitAndPrint(window, 0, "Natural", Vector2f(70, 364));

        waitAndPrint(window, 3, "Reflection!", Vector2f(70, 434));
      }

      if (loopCount == 2) {
        waitAndPrint(window, 0, "In this game,", Vector2f(70, 344));

        waitAndPrint(window, 4, "you control the blue circle",
                     Vector2f(70, 414));
      }

      if (loopCount == 3) {
        waitAndPrint(window, 0, "You need to use mirrors like",
                     Vector2f(70, 344));

        waitAndPrint(window, 0, "the one above you to reflect",
                     Vector2f(70, 414));

        waitAndPrint(window, 2, "light into the yellow block",
                     Vector2f(70, 484));

        waitAndPrint(window, 0, "Mirror", Vector2f(170, 280));

        waitAndPrint(window, 6, "Light", Vector2f(500, 210));
      }

      if (loopCount == 4) {
        waitAndPrint(window, 0, "You can interact with these",
                     Vector2f(70, 344));

        waitAndPrint(window, 5, "mirrors by pushing them", Vector2f(70, 414));
      }

      if (loopCount == 5) {
        waitAndPrint(window, 0, "If you ever get stuck,", Vector2f(70, 344));

        waitAndPrint(window, 5, "press 'R' to reset the level",
                     Vector2f(70, 414));
      }
    }

    if (levelNum == 1) {
      if (loopCount == 0) {
        waitAndPrint(window, 0, "You can push multiple", Vector2f(70, 344));

        waitAndPrint(window, 5, "mirrors at the same time", Vector2f(70, 414));
      }
    }

    if (levelNum == 2) {
      if (loopCount == 0) {
        waitAndPrint(window, 0, "Sometimes, you will have to",
                     Vector2f(70, 404));

        waitAndPrint(window, 0, "reflect the light around", Vector2f(70, 474));

        waitAndPrint(window, 6, "obstacles", Vector2f(70, 544));
      }
    }

    if (levelNum == 3) {
      if (loopCount == 0) {
        waitAndPrint(window, 0, "Watch out! If you reflect", Vector2f(70, 404));

        waitAndPrint(window, 0, "light into the purple block,",
                     Vector2f(70, 474));

        waitAndPrint(window, 6, "you lose the level", Vector2f(70, 544));
      }

      if (loopCount == 2) {
        waitAndPrint(window, 0, "You'll need to plan ahead", Vector2f(70, 404));

        waitAndPrint(window, 0, "to make sure the light doesn't",
                     Vector2f(70, 474));

        waitAndPrint(window, 6, "hit the purple block", Vector2f(70, 544));
      }
    }
  }

  void waitAndPrint(RenderWindow *window, int upTime, std::string message,
                    Vector2f pos) {
    text->setString(message);
    text->setPosition(pos);

    if (message == "Mirror") {
      text->setFillColor(Color(210, 180, 140));
    }

    if (message == "Light") {
      text->setFillColor(Color::Cyan);
    }

    if (upTime == 0) {
      window->draw(*text);
    }

    clock.restart();
    while (clock.getElapsedTime().asSeconds() < upTime) {
      window->draw(*text);
      window->display();
    }
  }

  ~TutorialText() {}
};
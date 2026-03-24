#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Player.h"
#include "MusicManager.h"
#include "localisation.h"

using namespace std;
using namespace sf;


int main()
{
    RenderWindow window(VideoMode({ 1280, 720 }), "Pack Mann");
    Font font("assets/fnt/Subert Gaming.otf");
    Clock clock;

    Localisation localisationManager;
    MusicManager musicManager;
    bool isPaused = false;
    int currentLang = 0;

    Vector2f pos = Vector2f(0, 0);
    int xSpeed = 80;
    int ySpeed = 80;

    Text text(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setString(localisationManager.GetLocalisedString(L"msg_debug", currentLang));
    text.setPosition(Vector2f(0, 0));

    Player player = Player({ 1280 / 2, 720 / 2 }, R"(assets/img/Akechi.png)");

    int currentColour = 0;
    Color textColours[6] = {
        Color::White,
        Color(226, 10, 255),
        Color(255, 115, 10),
        Color(33, 74, 255),
        Color(255, 247, 0),
        Color(255, 0, 0)
    };

    while (window.isOpen())
    {
        float delta = clock.restart().asSeconds();

        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                    if (isPaused)
                        musicManager.Resume();
                    else
                        musicManager.Pause();

                    isPaused = !isPaused;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::L) {
                    if (isPaused)
                        musicManager.Resume();
                    else
                        musicManager.Pause();

                    isPaused = !isPaused;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                    currentLang += 1;
                    currentLang %= 3;
                    text.setString(localisationManager.GetLocalisedString(L"msg_debug", currentLang));
                }
            }
        }

        if (window.hasFocus()) {            
            if (Keyboard::isKeyPressed(Keyboard::Key::P))
                musicManager.Play("papaoutai");

            if (Keyboard::isKeyPressed(Keyboard::Key::Backspace))
                musicManager.Stop();
        }
        pos = Vector2f(pos.x + (xSpeed * delta), pos.y + (ySpeed * delta));
        
        FloatRect textRect = text.getGlobalBounds();

        if (pos.x > 1280 - textRect.size.x || pos.x < 0) {
            xSpeed *= -1;
            currentColour += 1;
            currentColour %= 6;
            pos.x += xSpeed * delta;
            text.setFillColor(textColours[currentColour]);
        }

        if (pos.y > 720 - textRect.size.y || pos.y < 0) {
            ySpeed *= -1;
            currentColour += 1;
            currentColour %= 6;
            pos.y += ySpeed * delta;
            text.setFillColor(textColours[currentColour]);
        }

        text.setPosition(pos);

        window.clear(Color::Black);
        window.draw(player.GetSprite());
        window.draw(text);
        window.display();
    }
}
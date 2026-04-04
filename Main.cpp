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
#include "Map.h"
#include "Interactables.h"
#include <filesystem>
#include "Wall.h"

using namespace std;
using namespace sf;

//auto hightForScreen = 720;
//unsigned int widthForScreen = 1280;
static Vector2u windowSize = {896, 992};

int main()
{
    int tileSize = 32;
    Map map(windowSize, tileSize);

    RenderWindow window(VideoMode(windowSize), "Pack Mann");
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

    Player player = Player({ (float)windowSize.x / 2, (float)windowSize.y / 2 }, R"(assets/img/Akechi.png)");

    int currentColour = 0;
    Color textColours[6] = {
        Color::White,
        Color(226, 10, 255),
        Color(255, 115, 10),
        Color(33, 74, 255),
        Color(255, 247, 0),
        Color(255, 0, 0)
    };

    SpawnPellets(map, windowSize);
   
    Wall wall(100, 100, 64, 64);

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

        if (pos.x > windowSize.x - textRect.size.x || pos.x < 0) {
            xSpeed *= -1;
            currentColour += 1;
            currentColour %= 6;
            pos.x += xSpeed * delta;
            text.setFillColor(textColours[currentColour]);
        }

        if (pos.y > windowSize.y - textRect.size.y || pos.y < 0) {
            ySpeed *= -1;
            currentColour += 1;
            currentColour %= 6;
            pos.y += ySpeed * delta;
            text.setFillColor(textColours[currentColour]);
        }//*/

        text.setPosition(pos);
        player.Update(delta, windowSize);
        for (int i = 0; i < wallCount; i++) player.CheckWalls(wallList[i].GetRect(), delta);

        window.clear(Color::Black);
        for (Pellet& pellet : pelletList) pellet.Draw(window);
        //for (Wall& wall : wallList) wall.Draw(window);
        for (Wall& wall : wallList) window.draw(wall.GetSprite());
        //window.draw(wall.GetSprite());
        window.draw(player.GetRect());
        window.draw(player.GetSprite());
        window.draw(text);
        window.display();
    }
}
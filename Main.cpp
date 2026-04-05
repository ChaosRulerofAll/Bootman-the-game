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

    bool gameWon = false;

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

    bool boostActive = false;
    float boostTimer = 0.0f;
    const float boostDuration = 5.0f;


    Text text(font);
    text.setCharacterSize(24);
    text.setOutlineThickness(3);
    text.setFillColor(Color::White);
    text.setString(localisationManager.GetLocalisedString(L"msg_debug", currentLang));
    text.setPosition(Vector2f(0, 0));

    float offsetX = max(0.0f, ((float)windowSize.x - (28 * tileSize)) / 2.0f);
    float offsetY = max(0.0f, ((float)windowSize.y - (31 * tileSize)) / 2.0f);

    Vector2f spawnPos(
        offsetX + 13 * tileSize + tileSize / 2.f,
        offsetY + 22.5f * tileSize + tileSize / 2.f
    );

    Player player = Player(spawnPos, R"(assets/img/Akechi.png)");

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
   
    // Wall wall(100, 100, 64, 64);

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
                else if (keyPressed->scancode == sf::Keyboard::Scancode::P) {
                    musicManager.Play("pandora");
                }
            }
        }

        if (window.hasFocus()) {            
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
        }

        text.setPosition(pos);
        player.Update(delta, windowSize);
        for (int i = 0; i < wallCount; i++) player.CheckWalls(wallList[i].GetRect(), delta);

        FloatRect playerBounds = player.GetRect().getGlobalBounds();
        for (auto it = pelletList.begin(); it != pelletList.end();) {
            if (it->IsActive() && playerBounds.findIntersection(it->GetBounds())) {
                it = pelletList.erase(it);
            }
            else {
                ++it;
            }
        }
        for (auto it = pPelletList.begin(); it != pPelletList.end();) {
            if (it->IsActive() && playerBounds.findIntersection(it->GetBounds())) {
                player.topSpeed *= 1.5f;
                boostActive = true;
                boostTimer = 0.0f;
                it = pPelletList.erase(it);
            }
            else {
                ++it;
            }
        }
        if (boostActive) {
            boostTimer += delta;
            if (boostTimer >= boostDuration) {
                boostActive = false;
                boostTimer = 0.0f;
                player.topSpeed = 150.0f;
            }
        }

        int pelletsRemaining = pelletList.size() + pPelletList.size();

        if (pelletsRemaining == 0 && !gameWon) {
            gameWon = true;
            cout << gameWon << " You Won!" << endl;
        }

        window.clear(Color::Black);
        for (Pellet& pellet : pelletList) pellet.Draw(window);
        for (PowerPellet& powerPellet : pPelletList) powerPellet.Draw(window);
        //for (Wall& wall : wallList) wall.Draw(window);
        for (Wall& wall : wallList) wall.GetSprite(&window);
        //window.draw(wall.GetSprite());
        //window.draw(player.GetRect());
        window.draw(player.GetSprite());
        window.draw(text);
        window.display();
    }
}
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "Player.h"
#include "MusicManager.h"
#include "localisation.h"
#include "Map.h"
#include "Interactables.h"
#include <filesystem>
#include "Wall.h"

using namespace std;
using namespace sf;

enum GameState {
    LANGUAGE,
    TITLE,
    GAMING,
    WIN,
    LOSE
};

float DifficultyTimeLimits[4] = {
    200,
    120,
    80,
    45
};

float RecordTimes[4] = {
    200,
    120,
    80,
    45
};

int CurrentDifficulty = 0;

//auto hightForScreen = 720;
//unsigned int widthForScreen = 1280;
static Vector2u windowSize = {896, 992};
GameState CurrentGameState = LANGUAGE;

Texture titleTexture;

int tileSize = 32;
int LoopCount = 0;

float timeLeft = 1;

Map gameMap(windowSize, tileSize);

RenderWindow window(VideoMode(windowSize), "Bootman Trials HD: III.14 First Chapter Epilogue - A Shattered Throughaway GAMER MIX");
Font font("assets/fnt/Subert Gaming.otf");
Clock updateClock;

Localisation localisationManager;
MusicManager musicManager;
bool isPaused = false;
int currentLang = 0;
int langCount = 4;

Vector2f hashtagGamingPos = Vector2f(0, 0);
int xSpeedGaming = 80;
int ySpeedGaming = 80;

Vector2f timeLeftPos = Vector2f(0, 0);
int xSpeedTimer = 80;
int ySpeedTimer = 80;

bool boostActive = false;
float boostTimer = 0.0f;
const float boostDuration = 5.0f;

Text hashtagGamingText(font);
Text timeRemainingText(font);
Text pressEnterText(font);

float offsetX = max(0.0f, ((float)windowSize.x - (28 * tileSize)) / 2.0f);
float offsetY = max(0.0f, ((float)windowSize.y - (31 * tileSize)) / 2.0f);

Vector2f spawnPos(
    offsetX + 13 * tileSize + tileSize / 2.f,
    offsetY + 23 * tileSize + tileSize / 2.f
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

void LanguageSelect(float delta) {
    while (const optional event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
            window.close();
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter ||
                keyPressed->scancode == sf::Keyboard::Scancode::Z)
                CurrentGameState = TITLE;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Left ||
                keyPressed->scancode == sf::Keyboard::Scancode::A) {
                currentLang -= 1;
                if (currentLang < 0) currentLang = langCount - 1;
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Right ||
                keyPressed->scancode == sf::Keyboard::Scancode::D) {
                currentLang += 1;
                currentLang %= langCount;
            }
        }
    }

    if (LoopCount == 0) {     
        hashtagGamingText.setFillColor(Color::White);
    }

    window.clear(Color::Black);

    hashtagGamingText.setCharacterSize(40);
    // hashtagGamingText.setString(localisationManager.GetLocalisedString(L"msg_lang_name", currentLang));
    hashtagGamingText.setString(localisationManager.GetLocalisedString(L"msg_lang_name", currentLang));
    hashtagGamingText.setPosition(Vector2f((windowSize.x / 2) - (hashtagGamingText.getGlobalBounds().size.x / 2), (windowSize.y / 2) - 30));
    window.draw(hashtagGamingText);

    hashtagGamingText.setCharacterSize(20);
    hashtagGamingText.setString(localisationManager.GetLocalisedString(L"msg_confirm_lang", currentLang));
    hashtagGamingText.setPosition(Vector2f((windowSize.x / 2) - (hashtagGamingText.getGlobalBounds().size.x / 2), (windowSize.y / 2) + 30));
    window.draw(hashtagGamingText);

    window.display();
}

void TitleScreen(float delta) {
    while (const optional event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
            window.close();
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter || 
                     keyPressed->scancode == sf::Keyboard::Scancode::Z)
                CurrentGameState = GAMING;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Left ||
                keyPressed->scancode == sf::Keyboard::Scancode::A) {
                CurrentDifficulty -= 1;
                if (CurrentDifficulty < 0) CurrentDifficulty = 3;

                timeRemainingText.setString(localisationManager.GetLocalisedString(L"msg_difficulty_" + to_wstring(CurrentDifficulty), currentLang));
                timeRemainingText.setPosition(Vector2f((windowSize.x / 2) - (timeRemainingText.getGlobalBounds().size.x / 2), 675));

                pressEnterText.setString(localisationManager.GetLocalisedString(L"msg_best_time", currentLang) + to_string(RecordTimes[CurrentDifficulty]));
                pressEnterText.setPosition(Vector2f((windowSize.x / 2) - (pressEnterText.getGlobalBounds().size.x / 2), 710));
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Right ||
                keyPressed->scancode == sf::Keyboard::Scancode::D) {
                CurrentDifficulty += 1;
                CurrentDifficulty %= 4;

                timeRemainingText.setString(localisationManager.GetLocalisedString(L"msg_difficulty_" + to_wstring(CurrentDifficulty), currentLang));
                timeRemainingText.setPosition(Vector2f((windowSize.x / 2) - (timeRemainingText.getGlobalBounds().size.x / 2), 675));

                pressEnterText.setString(localisationManager.GetLocalisedString(L"msg_best_time", currentLang) + to_string(RecordTimes[CurrentDifficulty]));
                pressEnterText.setPosition(Vector2f((windowSize.x / 2) - (pressEnterText.getGlobalBounds().size.x / 2), 710));
            }
        }
    }

    if (LoopCount == 0) {
        // musicManager.Play("skyrunner");        
        hashtagGamingText.setFillColor(Color::White);
        hashtagGamingText.setCharacterSize(30);
        hashtagGamingText.setString(localisationManager.GetLocalisedString(L"msg_title", currentLang));
        hashtagGamingText.setPosition(Vector2f((windowSize.x / 2) - (hashtagGamingText.getGlobalBounds().size.x / 2), 575));

        timeRemainingText.setFillColor(Color::White);
        timeRemainingText.setCharacterSize(24);
        timeRemainingText.setString(localisationManager.GetLocalisedString(L"msg_difficulty_" + to_wstring(CurrentDifficulty), currentLang));
        timeRemainingText.setPosition(Vector2f((windowSize.x / 2) - (timeRemainingText.getGlobalBounds().size.x / 2), 675));

        pressEnterText.setFillColor(Color::White);
        pressEnterText.setCharacterSize(20);
        pressEnterText.setString(localisationManager.GetLocalisedString(L"msg_best_time", currentLang) + to_string(RecordTimes[CurrentDifficulty]));
        pressEnterText.setPosition(Vector2f((windowSize.x / 2) - (pressEnterText.getGlobalBounds().size.x / 2), 710));

        titleTexture.loadFromFile("assets/img/titleScreen.png");
    }

   sf::Sprite sprite(titleTexture);
    sprite.setPosition({ 0, 0 });

    window.clear(Color::Black);
    window.draw(sprite);
    window.draw(hashtagGamingText);
    window.draw(timeRemainingText);
    window.draw(pressEnterText);
    window.display();

    if (CurrentGameState != TITLE) {
        titleTexture.~Texture();
    }
}

void PacManGaming(float delta) {
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
        }
    }

    if (window.hasFocus()) {
        if (Keyboard::isKeyPressed(Keyboard::Key::Backspace))
            musicManager.Stop();
    }

    timeLeft -= delta;

    if (LoopCount == 0) {
        timeLeft = 120;
        player.SetPos(spawnPos);

        musicManager.Play("pandora");
        hashtagGamingText.setCharacterSize(24);
        hashtagGamingText.setOutlineThickness(3);
        hashtagGamingText.setFillColor(Color::White);
        hashtagGamingText.setString(localisationManager.GetLocalisedString(L"msg_debug", currentLang));
        hashtagGamingText.setPosition(Vector2f(0, 0));


        timeRemainingText.setCharacterSize(24);
        timeRemainingText.setOutlineThickness(3);
        timeRemainingText.setFillColor(Color::White);
        timeRemainingText.setString(localisationManager.GetLocalisedString(L"msg_time_remaining", currentLang) + to_string(timeLeft));

        timeLeftPos = Vector2f(windowSize.x - (timeRemainingText.getGlobalBounds().size.x), windowSize.y - (timeRemainingText.getGlobalBounds().size.y));
        timeRemainingText.setPosition(timeLeftPos);

        SpawnPellets(gameMap, windowSize);
    }

    timeRemainingText.setString(localisationManager.GetLocalisedString(L"msg_time_remaining", currentLang) + to_string(timeLeft));
    hashtagGamingPos = Vector2f(hashtagGamingPos.x + (xSpeedGaming * delta), hashtagGamingPos.y + (ySpeedGaming * delta));
    timeLeftPos = Vector2f(timeLeftPos.x + (xSpeedTimer * delta), timeLeftPos.y + (ySpeedTimer * delta));

    FloatRect textRect = hashtagGamingText.getGlobalBounds();
    FloatRect textRectTimer = timeRemainingText.getGlobalBounds();

    if (hashtagGamingPos.x > windowSize.x - textRect.size.x || hashtagGamingPos.x < 0) {
        xSpeedGaming *= -1;
        currentColour += 1;
        currentColour %= 6;
        hashtagGamingPos.x += xSpeedGaming * delta;
        hashtagGamingText.setFillColor(textColours[currentColour]);
    }

    if (hashtagGamingPos.y > windowSize.y - textRect.size.y || hashtagGamingPos.y < 0) {
        ySpeedGaming *= -1;
        currentColour += 1;
        currentColour %= 6;
        hashtagGamingPos.y += ySpeedGaming * delta;
        hashtagGamingText.setFillColor(textColours[currentColour]);
    }

    if (timeLeftPos.x > windowSize.x - textRectTimer.size.x || timeLeftPos.x < 0) {
        xSpeedTimer *= -1;
        currentColour += 1;
        currentColour %= 6;
        timeLeftPos.x += xSpeedTimer * delta;
        timeRemainingText.setFillColor(textColours[currentColour]);
    }

    if (timeLeftPos.y > windowSize.y - textRectTimer.size.y || timeLeftPos.y < 0) {
        ySpeedTimer *= -1;
        currentColour += 1;
        currentColour %= 6;
        timeLeftPos.y += ySpeedTimer * delta;
        timeRemainingText.setFillColor(textColours[currentColour]);
    }

    hashtagGamingText.setPosition(hashtagGamingPos);
    timeRemainingText.setPosition(timeLeftPos);
    player.Update(delta, windowSize);
    for (int i = 0; i < wallCount; i++) player.CheckWalls(wallList[i].GetRect(), delta);

    float yPickupSize = 1.1f;

    if (player.GetCurrentMoveDir().x != 0) yPickupSize = 1.8;

    FloatRect playerPickupBounds = player.GetRect().getGlobalBounds();
    playerPickupBounds.position = { playerPickupBounds.position.x - (((playerPickupBounds.size.x * 1.1f) - playerPickupBounds.size.x) / 2) ,
                                    playerPickupBounds.position.y - (((playerPickupBounds.size.y * yPickupSize) - playerPickupBounds.size.y) / 2) };
    playerPickupBounds.size = { playerPickupBounds.size.x * 1.1f, playerPickupBounds.size.y * yPickupSize };

    RectangleShape soraPickupBounds(playerPickupBounds.size);
    soraPickupBounds.setPosition(playerPickupBounds.position);
    soraPickupBounds.setFillColor(Color::Cyan);

    for (auto it = pelletList.begin(); it != pelletList.end();) {
        if (it->IsActive() && playerPickupBounds.findIntersection(it->GetBounds())) {
            it = pelletList.erase(it);
        }
        else {
            ++it;
        }
    }
    for (auto it = pPelletList.begin(); it != pPelletList.end();) {
        if (it->IsActive() && playerPickupBounds.findIntersection(it->GetBounds())) {
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

    window.clear(Color::Black);
    for (Pellet& pellet : pelletList) pellet.Draw(window);
    for (PowerPellet& powerPellet : pPelletList) powerPellet.Draw(window);
    for (Wall& wall : wallList) wall.GetSprite(&window);
    window.draw(player.GetSprite());
    window.draw(hashtagGamingText);
    window.draw(timeRemainingText);
    window.display();

    if (pelletsRemaining == 0)
    {
        CurrentGameState = WIN;
    }
    else if (timeLeft <= 0)
    {
        CurrentGameState = LOSE;
    }
}

void GameOver(float delta, bool won) {
    while (const optional event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
            window.close();
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter ||
                keyPressed->scancode == sf::Keyboard::Scancode::Z)
                CurrentGameState = TITLE;
        }
    }

    if (window.hasFocus()) {
        if (Keyboard::isKeyPressed(Keyboard::Key::Backspace))
            musicManager.Stop();
    }

    if (LoopCount == 0) {
        musicManager.Stop();

        pressEnterText.setCharacterSize(35);
        pressEnterText.setOutlineThickness(3);
        pressEnterText.setFillColor(Color::White);
        pressEnterText.setString(localisationManager.GetLocalisedString(L"msg_return_to_title", currentLang));

        pressEnterText.setPosition(Vector2f((windowSize.x / 2) - (pressEnterText.getGlobalBounds().size.x / 2), (windowSize.y / 2) - 75));

        if (won) {
            if (timeLeft < RecordTimes[CurrentDifficulty]) {
                RecordTimes[CurrentDifficulty] = timeLeft;
                hashtagGamingText.setString(localisationManager.GetLocalisedString(L"msg_new_record", currentLang));
            } else 
                hashtagGamingText.setString(localisationManager.GetLocalisedString(L"msg_celebrate", currentLang));
            timeRemainingText.setString(localisationManager.GetLocalisedString(L"msg_win", currentLang));
        }
        else {

            hashtagGamingText.setString(localisationManager.GetLocalisedString(L"msg_lose", currentLang));
            timeRemainingText.setString(localisationManager.GetLocalisedString(L"msg_game_over", currentLang));
        }

        timeRemainingText.setPosition(timeLeftPos);
        timeLeft = 0;
    }

    timeLeft += delta;

    hashtagGamingPos = Vector2f(hashtagGamingPos.x + (xSpeedGaming * delta), hashtagGamingPos.y + (ySpeedGaming * delta));
    timeLeftPos = Vector2f(timeLeftPos.x + (xSpeedTimer * delta), timeLeftPos.y + (ySpeedTimer * delta));

    FloatRect textRect = hashtagGamingText.getGlobalBounds();
    FloatRect textRectTimer = timeRemainingText.getGlobalBounds();

    if (hashtagGamingPos.x > windowSize.x - textRect.size.x || hashtagGamingPos.x < 0) {
        xSpeedGaming *= -1;
        currentColour += 1;
        currentColour %= 6;
        hashtagGamingPos.x += xSpeedGaming * delta;
        hashtagGamingText.setFillColor(textColours[currentColour]);
    }

    if (hashtagGamingPos.y > windowSize.y - textRect.size.y || hashtagGamingPos.y < 0) {
        ySpeedGaming *= -1;
        currentColour += 1;
        currentColour %= 6;
        hashtagGamingPos.y += ySpeedGaming * delta;
        hashtagGamingText.setFillColor(textColours[currentColour]);
    }

    if (timeLeftPos.x > windowSize.x - textRectTimer.size.x || timeLeftPos.x < 0) {
        xSpeedTimer *= -1;
        currentColour += 1;
        currentColour %= 6;
        timeLeftPos.x += xSpeedTimer * delta;
        timeRemainingText.setFillColor(textColours[currentColour]);
    }

    if (timeLeftPos.y > windowSize.y - textRectTimer.size.y || timeLeftPos.y < 0) {
        ySpeedTimer *= -1;
        currentColour += 1;
        currentColour %= 6;
        timeLeftPos.y += ySpeedTimer * delta;
        timeRemainingText.setFillColor(textColours[currentColour]);
    }

    hashtagGamingText.setPosition(hashtagGamingPos);
    timeRemainingText.setPosition(timeLeftPos);

    window.clear(Color::Black);

    if (timeLeft < 5) {
        if (!won) {
            for (Pellet& pellet : pelletList) pellet.Draw(window);
            for (PowerPellet& powerPellet : pPelletList) powerPellet.Draw(window);
        }

        for (Wall& wall : wallList) wall.GetSprite(&window);

        window.draw(hashtagGamingText);
        window.draw(timeRemainingText);
    }
    else {
        window.draw(pressEnterText);
    }
    window.display();
}

int main()
{
    GameState prevGameState = CurrentGameState;

    std::ifstream fin("Assets/dat/score.sav");

    if (!fin) {
        std::ofstream outfile("Assets/dat/score.sav");
        for (int i = 0; i < 4; i++)
            outfile << RecordTimes[i] << endl;
        outfile.close();
    }
    else {
        string line;
        int i = 0;
        while (std::getline(fin, line)) {
            if (i >= 4) continue;
            RecordTimes[i] = stof(line);
            i++;
        }
    }

    fin.close();

    while (window.isOpen())
    {
        float delta = updateClock.restart().asSeconds();
        
        switch (CurrentGameState) {
            case LANGUAGE:
                LanguageSelect(delta);
                break;
            case TITLE:
                TitleScreen(delta);
                break;
            case GAMING:
                PacManGaming(delta);
                break;
            case WIN:
                GameOver(delta, true);
                break;
            case LOSE:
                GameOver(delta, false);
                break;
        }

        LoopCount += 1;
        if (CurrentGameState != prevGameState) {
            LoopCount = 0;
            prevGameState = CurrentGameState;
        }
    }

    std::ofstream outfile("Assets/dat/score.sav");
    for (int i = 0; i < 4; i++)
        outfile << RecordTimes[i] << endl;
    outfile.close();

    return 0;
}
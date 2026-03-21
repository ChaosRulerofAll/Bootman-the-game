#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
using namespace sf;


int main()
{
    RenderWindow window(VideoMode({ 1280, 720 }), "Pack Mann");
    Font font("assets/fnt/Subert Gaming.otf");
    Clock clock;

    Text text(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setString("me when im #Gaming");
    text.setPosition(Vector2f(0, 0));

    Music music("assets/snd/mus/skyrunner.ogg");
    music.setLoopPoints({seconds(33.443356), seconds(58.435034)});
    music.setLooping(true);
    music.play();

    Vector2f pos = Vector2f(0, 0);
    int xSpeed = 80;
    int ySpeed = 80;

    int currentColour = 0;
    Color textColours[6] = {
        Color::White,
        Color(226, 10, 255),
        Color(255, 115, 10),
        Color(33, 74, 255),
        Color(255, 247, 0),
        Color(255, 0, 0)
    };

    // run the program as long as the window is open
    while (window.isOpen())
    {
        float delta = clock.restart().asSeconds();

        // check all the window's events that were triggered since the last iteration of the loop
        while (const optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<Event::Closed>())
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
            window.close();

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
        window.draw(text);
        window.display();
    }
}
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
    Font font("assets/Subert Gaming.otf");
    Clock clock;

    Text text(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setString("me when im #Gaming");
    text.setPosition(Vector2f(0, 0));

    float xPos = 0;

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
        xPos += delta * 40;

        text.setPosition(Vector2f(xPos, xPos));

        window.clear(Color::Black);
        window.draw(text);
        window.display();
    }
}
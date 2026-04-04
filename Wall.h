#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

using namespace sf;

class Wall : Transformable
{
public:
	Wall();
	Wall(int x, int y, int w, int h);
	Wall(int x, int y);

	sf::RectangleShape GetSprite();
	sf::FloatRect GetRect();


private:
	Vector2f pos;
	Vector2f size;
};


#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Wall : Transformable
{
private:
	Wall();
	Wall(int x, int y, int w, int h);
	Wall(int x, int y);
};


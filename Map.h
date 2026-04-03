#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Map
{
	private:
		Vector2u windowSize;
		unsigned int tilePixelSize;

		// W = wall, E = empty, P = pellet, p = PowerPellet, B = Bootman
		const char tileType[31][28] = {
			{'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
			{'W', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'W', 'W', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'W'},
			{'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W'},
			{'W', 'p', 'W', 'E', 'E', 'W', 'P', 'W', 'E', 'E', 'E', 'W', 'P', 'W', 'W', 'P', 'W', 'E', 'E', 'E', 'W', 'P', 'W', 'E', 'E', 'W', 'p', 'W'},
			{'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W'},
			{'W', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'W'},
			{'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W'},
			{'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W'},
			{'W', 'P', 'P', 'P', 'P', 'P', 'P', 'W', 'W', 'P', 'P', 'P', 'P', 'W', 'W', 'P', 'P', 'P', 'P', 'W', 'W', 'P', 'P', 'P', 'P', 'P', 'P', 'W'},
			{'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W'},
			{'E', 'E', 'E', 'E', 'E', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'E', 'E', 'E', 'E', 'E'},
			{'E', 'E', 'E', 'E', 'E', 'W', 'P', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'P', 'W', 'E', 'E', 'E', 'E', 'E'},
			{'E', 'E', 'E', 'E', 'E', 'W', 'P', 'W', 'W', 'E', 'W', 'W', 'W', 'E', 'E', 'W', 'W', 'W', 'E', 'W', 'W', 'P', 'W', 'E', 'E', 'E', 'E', 'E'},
			{'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'E', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'E', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W'},
			{'E', 'E', 'E', 'E', 'E', 'E', 'P', 'E', 'E', 'E', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'E', 'E', 'E', 'P', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'E', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'E', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W'},
			{'E', 'E', 'E', 'E', 'E', 'W', 'P', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'P', 'W', 'E', 'E', 'E', 'E', 'E'},
			{'E', 'E', 'E', 'E', 'E', 'W', 'P', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'P', 'W', 'E', 'E', 'E', 'E', 'E'},
			{'E', 'E', 'E', 'E', 'E', 'W', 'P', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'P', 'W', 'E', 'E', 'E', 'E', 'E'},
			{'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W'},
			{'W', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'W', 'W', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'W'},
			{'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W'},
			{'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'P', 'W'},
			{'W', 'p', 'P', 'P', 'W', 'W', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'B', 'B', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'W', 'W', 'P', 'P', 'p', 'W'},
			{'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W'},
			{'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W'},
			{'W', 'P', 'P', 'P', 'P', 'P', 'P', 'W', 'W', 'P', 'P', 'P', 'P', 'W', 'W', 'P', 'P', 'P', 'P', 'W', 'W', 'P', 'P', 'P', 'P', 'P', 'P', 'W'},
			{'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W'},
			{'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W', 'W', 'P', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'P', 'W'},
			{'W', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'W'},
			{'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'}
		};
		//const static unsigned long long int tileData = 4;

	public:
		Map(Vector2u screenS, unsigned int tileS)
		{
			windowSize = screenS;
			tilePixelSize = tileS;
			//cout << tileData << endl;
		}
		Map() 
		{
			windowSize = Vector2u(0, 0);
			tilePixelSize = 0;
		}

		char getMapObject(int X, int Y) {
			return tileType[Y % 31][X % 28];
		}
};


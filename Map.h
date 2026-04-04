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
		char tileType[31][28] = {
			{'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'E', 'W'},
			{'W', 'E', 'W', 'E', 'E', 'W', 'E', 'W', 'E', 'E', 'E', 'W', 'E', 'W', 'W', 'E', 'W', 'E', 'E', 'E', 'W', 'E', 'W', 'E', 'E', 'W', 'E', 'W'},
			{'W', 'E', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'W', 'W', 'W', 'E', 'W', 'W', 'E', 'W', 'W', 'W', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W', 'W', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
			{'W', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'W'},
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

		}
		 char GetTileType(int row, int col) const {

			return tileType[row][col];
		}

		 int GetTilePixelSize(int pixelSize) {
			 return tilePixelSize;
		 }
};


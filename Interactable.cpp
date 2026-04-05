#include <iostream>
#include <vector>
#include "Map.h"
#include "Interactables.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;
using namespace std;

vector<Pellet> pelletList;
vector<Wall> wallList;
vector<PowerPellet> pPelletList;
int wallCount;
int pixelSize;

Interactables::~Interactables() {};


void SpawnPellets(Map& mapLayout, Vector2u windowSize) {

	int tileSize = mapLayout.GetTilePixelSize(pixelSize);
	float offsetX = max(0.0f, ((int)windowSize.x - (28 * tileSize)) / 2.0f);
	float offsetY = max(0.0f, ((int)windowSize.y - (31 * tileSize)) / 2.0f);

	for (int row = 0; row < 31; row++) {
		for (int col = 0; col < 28; col++) {
			if (mapLayout.GetTileType(row, col) == 'P') {
				Vector2f position(offsetX + col * tileSize, offsetY + row * tileSize);
				pelletList.push_back(Pellet(position));
			};
			if (mapLayout.GetTileType(row, col) == 'p') {
				Vector2f PowerPelletPosition(offsetX + col * tileSize - 4.0f, offsetY + row * tileSize - 4.0f);
				pPelletList.push_back(PowerPellet(PowerPelletPosition));
			}
			if (mapLayout.GetTileType(row, col) == 'W') {
				Vector2f positionWall(offsetX + col * tileSize, offsetY + row * tileSize);
				wallList.push_back(Wall (positionWall.x, positionWall.y));
				wallCount++;
			}

		};
	};
	cout << "First Pellet Position Is: " << offsetX << ", " << offsetY << endl;
	cout << "Power Pellet Count Is: " << pPelletList.size() << endl;

}

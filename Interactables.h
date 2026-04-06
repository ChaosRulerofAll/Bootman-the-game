#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Wall.h"

using namespace std;
using namespace sf;

class Interactables {
public:
	Interactables(Vector2f pos, int scoreValue, int Size, Color color) : position(pos), score(scoreValue), size(Size), col(color), isActive(true) {
		pellet.setRadius(Size);
		pellet.setFillColor(color);
		pellet.setOutlineColor(Color::Black);
		pellet.setPosition({pos.x - 3, pos.y - 3});
	};

	~Interactables();

	void Draw(RenderWindow& window) {
		if (isActive) {
			window.draw(pellet);
		}
	}

	virtual void OnCollect() {
		isActive = false;
	};

	bool IsActive() const { return isActive;}

	FloatRect GetBounds() const{ return pellet.getGlobalBounds(); };

	void addScore(int value) {
		score += value;
	}

	int getScore() {
		return score;
	}

private:
	int score;
	Vector2f position;
	CircleShape pellet;
	int size;
	Color col;

protected:
	bool isActive;

};

class Pellet : public Interactables {
public:
	Pellet(Vector2f pos) : Interactables(pos, 10, 3, Color::White) {}
};


class PowerPellet : public Interactables {
public:
	PowerPellet(Vector2f pos) : Interactables(pos, 10, 6, Color::Red) {}

	void OnCollect() override {
		isActive = false;
	}
};

extern vector<Pellet> pelletList;
extern vector<PowerPellet> pPelletList;
extern vector<Wall> wallList;
extern int wallCount;
void SpawnPellets(Map& map, Vector2u windowSize);
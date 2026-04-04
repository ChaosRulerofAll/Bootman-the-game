#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Player
{
	public:
		Vector2f screenPos;
		float moveSpeed = 0;
		float topSpeed = 150;

		Player();
		Player(Vector2f pos, std::string spritePath);
		void Update(float deltaTime);
		void CheckWalls(FloatRect rect, float deltaTime);

		sf::Sprite GetSprite();
		sf::RectangleShape GetRect();
	private:
		void ParseXML(string path);
		void SetAnimation();

		Texture spriteTexture;
		Vector2f moveDir;
		Vector2f prevMoveDir;
		float animSpeed = 0.05;
		int currentAnimRect = 0;
		string currentAnimName = "us";

		float nextFrameCounter = 0;
		
		map<string, vector<IntRect>> animList;
};


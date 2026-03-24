#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;

class Player
{
	public:
		Vector2f screenPos;
		float moveSpeed = 0;
		float topSpeed = 200;

		Player();
		Player(Vector2f pos, std::string spritePath);
		void Update(float deltaTime);

		sf::Sprite GetSprite();
	private:
		Texture spriteTexture;
		Vector2f moveDir;
		float animSpeed = 0.05;
		int currentRect = 0;

		float nextFrameCounter = 0;
		
		IntRect idleRect[1] = {
			IntRect({320, 0}, {40, 55})
		};

		IntRect walkRect[8] = {
			IntRect({0, 0}, {40, 55}),
			IntRect({40, 0}, {40, 55}),
			IntRect({80, 0}, {40, 55}),
			IntRect({120, 0}, {40, 55}),
			IntRect({160, 0}, {40, 55}),
			IntRect({200, 0}, {40, 55}),
			IntRect({240, 0}, {40, 55}),
			IntRect({280, 0}, {40, 55})
		};

		// Sprite sprite;
};


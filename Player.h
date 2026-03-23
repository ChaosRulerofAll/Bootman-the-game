#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;

class Player
{
	public:
		Vector2f screenPos;
		float moveSpeed = 0;
		float topSpeed = 20;

		Player();
		Player(Vector2f pos, std::string spritePath);
		void Update(float delta);

		sf::Sprite GetSprite();
	private:
		Texture spriteTexture;
		Sprite sprite;
};


#include <iostream>
#include "Player.h"

Player::Player(Vector2f pos, std::string spritePath)
{
	this->screenPos = pos;
	this->moveSpeed = 0;

    Texture texture;
    if (!texture.loadFromFile(spritePath, false, sf::IntRect({0, 0}, {100, 100})))
    {
        std::cerr << "failed to load image " << R"(spritePath)" << std::endl;
        exit(1);
    }

    this->spriteTexture = texture;
    sprite.setTexture(spriteTexture);
}

sf::Sprite Player::GetSprite() {
    sf::Sprite sprite(spriteTexture);
    sprite.setOrigin({ 50, 50 });
    sprite.setPosition(screenPos);
    return sprite;
}
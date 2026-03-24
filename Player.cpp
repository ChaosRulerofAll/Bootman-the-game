#include <iostream>
#include "Player.h"

Player::Player(Vector2f pos, std::string spritePath)
{
	this->screenPos = pos;
	this->moveSpeed = 0;

    Texture texture;
    if (!texture.loadFromFile("assets/img/sora.png"))
    {
        std::cerr << "failed to load image " << R"(spritePath)" << std::endl;
        exit(1);
    }

    this->spriteTexture = texture;
}

sf::Sprite Player::GetSprite() {
    sf::Sprite sprite(spriteTexture);

    sprite.setTextureRect(sf::IntRect({320, 0}, {40, 55}));
    sprite.setOrigin({ (float)(sprite.getTextureRect().size.x / 2) , (float)sprite.getTextureRect().size.y });
    sprite.setScale({2, 2});
    sprite.setPosition(screenPos);
    return sprite;
}
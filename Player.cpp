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

    if (moveDir.length() < 0.5)
        sprite.setTextureRect(idleRect[0]);
    else
        sprite.setTextureRect(walkRect[currentRect]);
    sprite.setOrigin({ (float)(sprite.getTextureRect().size.x / 2) , (float)sprite.getTextureRect().size.y });
    sprite.setScale({2, 2});
    sprite.setPosition(screenPos);
    return sprite;
}

void Player::Update(float deltaTime) {
    if (moveDir.length() > 0.5){
        nextFrameCounter += deltaTime;
        if (nextFrameCounter >= animSpeed) {
            nextFrameCounter -= animSpeed;
            currentRect += 1;
            currentRect %= sizeof(walkRect)/sizeof(walkRect[0]);
        }
    }

    moveDir = Vector2f(0, 0);

    if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
        moveDir.x -= 1;
    if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
        moveDir.x += 1;
    if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))
        moveDir.y -= 1;
    if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))
        moveDir.y += 1;

    if (moveDir.x != 0 || moveDir.y != 0)
        moveDir = moveDir.normalized();

    screenPos.x += moveDir.x * topSpeed * deltaTime;
    screenPos.y += moveDir.y * topSpeed * deltaTime;
}
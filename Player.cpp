#include <iostream>
#include <fstream>
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

    ParseXML("assets/img/sora.xml");

    this->spriteTexture = texture;
}

sf::Sprite Player::GetSprite() {
    sf::Sprite sprite(spriteTexture);

    if (moveDir.length() < 0.5)
        sprite.setTextureRect(animList[currentAnimName][0]);
    else
        sprite.setTextureRect(animList[currentAnimName][currentAnimRect]);
    sprite.setOrigin({ (float)(sprite.getTextureRect().size.x / 2) , (float)sprite.getTextureRect().size.y });
    sprite.setScale({2, 2});
    sprite.setPosition(screenPos);
    return sprite;
}

void Player::ParseXML(string path) {
    std::ifstream spriteSheet(path);

    if (spriteSheet.is_open()) {
        string line;
        string spriteName;
        int x, y, w, h;
        string currentAnim = "none";
        vector<IntRect> currentAnimRects(0);
        IntRect currentRect;

        while (std::getline(spriteSheet, line)) {
            if (line.find("<sprite") == string::npos) continue;
            
            string::size_type startPos = 0;
            string::size_type endPos = 0;

            startPos = line.find("\"") + 1;
            endPos = line.substr(startPos).find("\"");
            spriteName = line.substr(startPos, endPos);
            line = line.substr(startPos + endPos + 1);

            startPos = line.find("\"") + 1;
            endPos = line.substr(startPos).find("\"");
            x = stoi(line.substr(startPos, endPos));
            line = line.substr(startPos + endPos + 1);

            startPos = line.find("\"") + 1;
            endPos = line.substr(startPos).find("\"");
            y = stoi(line.substr(startPos, endPos));
            line = line.substr(startPos + endPos + 1);

            startPos = line.find("\"") + 1;
            endPos = line.substr(startPos).find("\"");
            w = stoi(line.substr(startPos, endPos));
            line = line.substr(startPos + endPos + 1);

            startPos = line.find("\"") + 1;
            endPos = line.substr(startPos).find("\"");
            h = stoi(line.substr(startPos, endPos));

            spriteName = spriteName.substr(0, spriteName.find("_"));
            currentRect = IntRect({ x, y }, { w, h });

            if (spriteName == currentAnim) {
                currentAnimRects.push_back(currentRect);
            }
            else
            {
                animList.insert(pair<string, vector<IntRect>>(currentAnim, currentAnimRects));
                
                currentAnimRects = vector<IntRect>(0);
                currentAnimRects.push_back(currentRect);
                currentAnim = spriteName;
            }
        }

        animList.insert(pair<string, vector<IntRect>>(currentAnim, currentAnimRects));
    }
}

void Player::Update(float deltaTime) {
    SetAnimation();

    if (prevMoveDir.length() > 0.5){
        nextFrameCounter += deltaTime;
        // cout << nextFrameCounter << endl;
        if (nextFrameCounter >= animSpeed) {
            nextFrameCounter -= animSpeed;
            currentAnimRect += 1;
            currentAnimRect %= animList[currentAnimName].size();
        }
    }
    else {
        currentAnimRect = 0;
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

    if (moveDir.x != 0 || moveDir.y != 0) {
        prevMoveDir = moveDir;
        moveDir = moveDir.normalized();
    }

    screenPos.x += moveDir.x * topSpeed * deltaTime;
    screenPos.y += moveDir.y * topSpeed * deltaTime;
}

void Player::SetAnimation() {
    if (moveDir.x == 0 && moveDir.y == 0) {
        if (prevMoveDir == Vector2f(-1, 0))
            currentAnimName = "ls";
        else if (prevMoveDir == Vector2f(1, 0))
            currentAnimName = "rs";
        else if (prevMoveDir == Vector2f(0, 1))
            currentAnimName = "ds";
        else if (prevMoveDir == Vector2f(0, -1))
            currentAnimName = "us";
        else if (prevMoveDir == Vector2f(1, -1))
            currentAnimName = "urs";
        else if (prevMoveDir == Vector2f(-1, -1))
            currentAnimName = "uls";
        else if (prevMoveDir == Vector2f(1, 1))
            currentAnimName = "drs";
        else if (prevMoveDir == Vector2f(-1, 1))
            currentAnimName = "dls";
    }
    else 
    {
        if (prevMoveDir == Vector2f(-1, 0))
            currentAnimName = "l";
        else if (prevMoveDir == Vector2f(1, 0))
            currentAnimName = "r";
        else if (prevMoveDir == Vector2f(0, 1))
            currentAnimName = "d";
        else if (prevMoveDir == Vector2f(0, -1))
            currentAnimName = "u";
        else if (prevMoveDir == Vector2f(1, -1))
            currentAnimName = "ur";
        else if (prevMoveDir == Vector2f(-1, -1))
            currentAnimName = "ul";
        else if (prevMoveDir == Vector2f(1, 1))
            currentAnimName = "dr";
        else if (prevMoveDir == Vector2f(-1, 1))
            currentAnimName = "dl";
    }
}
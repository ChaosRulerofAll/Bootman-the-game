#include "Wall.h"

Wall::Wall() {
	size = { 32, 32 };
	pos = { 16, 16 };
}

Wall::Wall(int x, int y) {
	size = { 25, 25 };
	pos = { (float) x, (float) y };
}

Wall::Wall(int x, int y, int w, int h) {
	size = { (float) w, (float) h };
	pos = { (float) x, (float) y };
}

void Wall::GetSprite(RenderWindow* window) {
	RectangleShape rect({size.x, size.y});
	rect.setFillColor(Color::Magenta);
	rect.setOrigin({ (float)(size.x / 2) , (float) size.y / 2 });
	rect.setPosition(pos);

	window->draw(rect);
}

FloatRect Wall::GetRect() {
	return (FloatRect({ pos.x - size.x / 2.0f , pos.y - size.y / 2.0f}, { size.x, size.y }));
}
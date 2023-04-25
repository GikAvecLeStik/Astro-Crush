#pragma once
class Player
{
	sf::Texture texture;
	sf::Sprite sprite;
	unsigned short x;

public:
	Player();
	void draw(sf::RenderWindow& i_window);
	void update();
};


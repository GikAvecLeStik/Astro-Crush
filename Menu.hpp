#pragma once
#include <iostream>
#define maxMenu 4
class Menu
{
	
public:
	Menu(float wid, float hei);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();

	int menuPressed() {
		return menuSelect;
	}
	~Menu();
private:
	int menuSelect;
	sf::Font font;
	sf::Text mainmenu[maxMenu];
};


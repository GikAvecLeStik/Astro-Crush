#pragma once
#include <iostream>
#define maxMenu 4
class Menu
{
	
public:
	Menu(float wid, float hei);
	void drawMenu(sf::RenderWindow& window);
	void moveUp();
	void moveDown();

	int menuPressed() {
		return menuSelect;
	}
	~Menu();
private:
	int menuSelect;
	sf::Text mainmenu[maxMenu];
};


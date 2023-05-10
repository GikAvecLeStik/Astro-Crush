#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.hpp"

Menu::Menu(float wid, float hei)
{
	mainmenu[0].setFillColor(sf::Color::White);
	mainmenu[0].setString("Jugar");
	mainmenu[0].setCharacterSize(1280);
	mainmenu[0].setPosition(700, 400);

	mainmenu[1].setFillColor(sf::Color::White);
	mainmenu[1].setString("Instrucciones");
	mainmenu[1].setCharacterSize(70);
	mainmenu[1].setPosition(160, 70);

	mainmenu[2].setFillColor(sf::Color::White);
	mainmenu[2].setString("Creditos");
	mainmenu[2].setCharacterSize(70);
	mainmenu[2].setPosition(160, 45);

	mainmenu[3].setFillColor(sf::Color::White);
	mainmenu[3].setString("Salir");
	mainmenu[3].setCharacterSize(70);
	mainmenu[3].setPosition(160, 22);

	menuSelect = -1;
}
Menu::~Menu()
{

}

void Menu::drawMenu(sf::RenderWindow& window)
{
	for (int i = 0; i < maxMenu; i++)
	{

		window.draw(mainmenu[i]);
	}
}

void Menu::moveUp()
{
	if (menuSelect - 1 >= 0)
	{
		mainmenu[menuSelect].setFillColor(sf::Color::White);
		menuSelect--;
		if (menuSelect == -1)
		{
			menuSelect = 2;
		}
		mainmenu[menuSelect].setFillColor(sf::Color::Yellow);
	}
}
void Menu::moveDown()
{
	if (menuSelect + 1 <= maxMenu)
	{
		mainmenu[menuSelect].setFillColor(sf::Color::White);
		menuSelect++;
		if (menuSelect == 4)
		{
			menuSelect = 0;
		}
		mainmenu[menuSelect].setFillColor(sf::Color::Yellow);
	}
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Menu.hpp"

Menu::Menu(float wid, float hei)
{
	if (!font.loadFromFile("Fonts/Pixelated Regular.ttf"))
	{
		std::cout << "no hay ninguna fuente";
	}
	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(sf::Color::Black);
	mainmenu[0].setString("Jugar");
	mainmenu[0].setCharacterSize(40);
	mainmenu[0].setPosition(480, 300);

	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(sf::Color::Black);
	mainmenu[1].setString("Instrucciones");
	mainmenu[1].setCharacterSize(40);
	mainmenu[1].setPosition(400, 350);

	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(sf::Color::Black);
	mainmenu[2].setString("Creditos");
	mainmenu[2].setCharacterSize(40);
	mainmenu[2].setPosition(360, 390);

	mainmenu[3].setFont(font);
	mainmenu[3].setFillColor(sf::Color::Black);
	mainmenu[3].setString("Salir");
	mainmenu[3].setCharacterSize(40);
	mainmenu[3].setPosition(640, 420);

	menuSelect = -1;
}
Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < maxMenu; ++i)
	{

		window.draw(mainmenu[i]);
	}
}

void Menu::moveUp()
{
	if (menuSelect - 1 >= 0)
	{
		mainmenu[menuSelect].setFillColor(sf::Color::Black);
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
		mainmenu[menuSelect].setFillColor(sf::Color::Black);
		menuSelect++;
		if (menuSelect == 4)
		{
			menuSelect = 0;
		}
		mainmenu[menuSelect].setFillColor(sf::Color::Yellow);
	}
}

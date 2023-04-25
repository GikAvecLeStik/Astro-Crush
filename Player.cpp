#include <SFML/Graphics.hpp>
#include "Player.hpp"

Player::Player() :
	x(0.5f*(320-16))
{
	texture.loadFromFile("Textures/nave.png");
	sprite.setTexture(texture);
}
void Player::draw (sf::RenderWindow& i_window)
{
	sprite.setPosition(160, 90);
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
	
	i_window.draw(sprite);
}
void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		sprite.rotate(-x);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		sprite.rotate(x);
}
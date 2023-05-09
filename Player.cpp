#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <cmath>

Player::Player() 
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
	movement.x = 250;
	movement.y = 250;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		sprite.rotate(-x * x_SPEED * det);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		sprite.rotate(x * x_SPEED * det);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			movimiento();
		}
	
}
void Player::dt()
{
	det = clock.restart().asSeconds();
}
double Player::Degtorad(double r)
{
	r *= 0.0174533;

	return r;
}
void Player::movimiento()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		applyThrust();

		movement.x += velx;
		movement.y += vely;



		sprite.move(movement.x*det, movement.y*det);

	}
	
	//movement.x = velocity * sin(0.0174533 * sprite.getRotation());
	//movement.y = velocity * -cos(0.0174533 * sprite.getRotation());

	//dx += movement.x * 0.2;
	//dy -= movement.y * 0.2;

	////dx = xVel * sin(Degtorad(sprite.getRotation()));
	////dy = yVel * -cos(Degtorad(sprite.getRotation()));

	//sprite.move(movement.x * -200 * det, movement.y * 200 * det);
}

void Player::applyThrust()
{
	/*
	   Assume 1 total unit of thrust is applied each time you hit the thrust button
	   so you break down the velocity into x and y components depending on the direction
	   your ship is facing.
	*/
	// thrustUnit is how much thrust each thrust button press gets you, it's arbitrary
	// and can be the 2.5 multiplier you're using in your question
	float thrustUnit = 1.0;
	_angle = (0.0174533 * sprite.getRotation());
	// now get the x and y thrust components of velocity based on your ship's direction
	// assuming 0 degrees is pointing to the right

	newVX = thrustUnit * cos(_angle);
	newVY = thrustUnit * sin(_angle); // radian conversion left out to save space

	// Update your ship's velocity
	updateVelocity(newVX, newVY);
}

void Player::updateVelocity(float newVX, float newVY)
{
	// update the x component
	velx += newVX;
	vely += newVY;
}

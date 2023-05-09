#pragma once
class Player
{
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Clock clock;

	
	unsigned short x = (0.5f * (320 - 16));
	unsigned short y;
	float dx;
	float dy;
	const unsigned char x_SPEED = 2.6;
	float thrustUnit = 1.0;
	float velocity= 200;
	sf::Vector2f movement;
	sf::Vector2f direccion;
	float newVX, newVY = 0.0;
	float velx, vely;
	float det;
	double _angle;
	

public:
	Player();
	void draw(sf::RenderWindow& i_window);
	void update();
	void dt();
	double Degtorad(double r);
	void movimiento();
	void applyThrust();
	void update


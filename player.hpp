#pragma once
#include <SFML/Graphics.hpp>

float DEGTORAD = 0.017453f;
const int W = 1280;
const int H = 720;

class Animation
{
    sf::Sprite sprite;

    public:
    float Frame, speed;
    void update();
    bool isEnd();


};

class Entity
{
    sf::Animation anim;

    public:
    float x,y,dx,dy,R,angle;
    bool life;
    void settings();


};

class Player
{
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Clock clock;

	unsigned short x = (0.5f * (320 - 16));
	unsigned short y;
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
    bool thrust();

	void dt();
	double Degtorad(double r);
	void movimiento();
//	void applyThrust();

};


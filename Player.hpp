#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>


const int W = 1280;
const int H = 720;
extern float DEGTORAD;


class Animation
{
public:
	float Frame, speed;
	sf::Sprite sprite;
	std::vector<sf::IntRect> frames;

	Animation() {}

	Animation(sf::Texture& t, int x, int y, int w, int h, int count, float Speed);

	void update();

	bool isEnd();
};

class Entity
{
public:
	float x, y, dx, dy, R, angle;
	bool life;
	std::string name;
	Animation anim;

	Entity();

	void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1);

	virtual void update() {};

	void draw(sf::RenderWindow& app);

	virtual ~Entity() {};
};

class asteroid : public Entity
{
public:
	asteroid();

	void update();
};

class Player : public Entity
{
public:
	bool thrust;

	Player();

	void update();
};

class bullet : public Entity
{
public:
	bullet();

	void  update();
};

bool isCollide(Entity* a, Entity* b);

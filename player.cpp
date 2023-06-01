#include "Player.hpp"
float DEGTORAD = 0.017453f;
Animation::Animation(sf::Texture& t, int x, int y, int w, int h, int count, float Speed)
{
    Frame = 0;
    speed = Speed;

    for (int i = 0; i < count; i++)
        frames.push_back(sf::IntRect(x + i * w, y, w, h));

    sprite.setTexture(t);
    sprite.setOrigin(w / 2, h / 2);
    sprite.setTextureRect(frames[0]);
}

void Animation::update()
{
    Frame += speed;
    int n = frames.size();
    if (Frame >= n) Frame -= n;
    if (n > 0) sprite.setTextureRect(frames[int(Frame)]);
}

bool Animation::isEnd()
{
    return Frame + speed >= frames.size();
}

Entity::Entity()
{
    life = 1;
}

void Entity::settings(Animation& a, int X, int Y, float Angle, int radius)
{
    anim = a;
    x = X; y = Y;
    angle = Angle;
    R = radius;
}

void Entity::draw(sf::RenderWindow& app)
{
    anim.sprite.setPosition(x, y);
    anim.sprite.setRotation(angle + 90);
    app.draw(anim.sprite);

    sf::CircleShape circle(R);
    circle.setFillColor(sf::Color(255, 0, 0, 170));
    circle.setPosition(x, y);
    circle.setOrigin(R, R);
}

asteroid::asteroid()
{
    dx = rand() % 8 - 4;
    dy = rand() % 8 - 4;
    name = "asteroid";
}

void asteroid::update()
{
    x += dx;
    y += dy;

    if (x > W) x = 0;  if (x < 0) x = W;
    if (y > H) y = 0;  if (y < 0) y = H;
}

Player::Player()
{
    name = "player";
}

void Player::update()
{
    if (thrust)
    {
        dx += cos(angle * DEGTORAD) * 0.1;
        dy += sin(angle * DEGTORAD) * 0.1;
    }
    else
    {
        dx *= 0.99;
        dy *= 0.99;
    }

    int maxSpeed = 5;
    float speed = sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed)
    {
        dx *= maxSpeed / speed;
        dy *= maxSpeed / speed;
    }

    x += dx;
    y += dy;

    if (x > W) x = 0; if (x < 0) x = W;
    if (y > H) y = 0; if (y < 0) y = H;
}

bullet::bullet()
{
    name = "bullet";
}

void bullet::update()
{
    dx = cos(angle * DEGTORAD) * 6;
    dy = sin(angle * DEGTORAD) * 6;

    x += dx;
    y += dy;

    if (x > W || x<0 || y>H || y < 0) life = 0;
}

bool isCollide(Entity* a, Entity* b)
{
    return (b->x - a->x) * (b->x - a->x) +
        (b->y - a->y) * (b->y - a->y) <
        (a->R + b->R) * (a->R + b->R);
}


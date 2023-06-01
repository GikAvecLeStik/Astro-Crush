#include "Player.hpp"
#include <cmath>
#include <list>

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

void runGame(sf::RenderWindow& app)
{
    srand(time(0));

    sf::Texture t1, t2, t3, t4;
    t1.loadFromFile("Textures/naveGud.png");
    t2.loadFromFile("Textures/espacio.png");
    t3.loadFromFile("Textures/balas.png");
    t4.loadFromFile("Textures/asteroides.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    sf::Sprite fondo(t2);

    Animation sBullet(t3, 0, 0, 32, 64, 16, 0.8);
    Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
    Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
    Animation sRock_small(t4, 0, 0, 64, 64, 16, 0.2);

    std::list<Entity*> entities;

    for (int i = 0; i < 3; i++)
    {
        asteroid* a = new asteroid();
        a->settings(sRock_small, rand() % W, rand() % H, rand() % 360, 25);
        entities.push_back(a);
    }

    // posicion del jugador
    Player* p = new Player();
    p->settings(sPlayer, W / 2, H / 2, 0, 20);
    entities.push_back(p);

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Z)
                {
                    bullet* b = new bullet();
                    b->settings(sBullet, p->x, p->y, p->angle, 10);
                    entities.push_back(b);
                }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) p->angle += 3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  p->angle -= 3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) p->thrust = true;
        else p->thrust = false;

        for (auto a : entities)
            for (auto b : entities)
            {
                if (a->name == "asteroid" && b->name == "bullet")
                    if (isCollide(a, b))
                    {
                        a->life = false;
                        b->life = false;

                        Entity* e = new Entity();
                        //              e->settings(sExplosion,a->x,a->y);
                        //              e->name="explosion";
                        entities.push_back(e);


                        for (int i = 0; i < 2; i++)
                        {
                            if (a->R == 15) continue;
                            Entity* e = new asteroid();
                            e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
                            entities.push_back(e);
                        }

                    }

                if (a->name == "player" && b->name == "asteroid")
                    if (isCollide(a, b))
                    {
                        b->life = false;

                        Entity* e = new Entity();
                        //              e->settings(sExplosion_ship,a->x,a->y);
                        //              e->name="explosion";
                        entities.push_back(e);

                        p->settings(sPlayer, W / 2, H / 2, 0, 20);
                        p->dx = 0; p->dy = 0;
                    }
            }

        if (rand() % 150 == 0)
        {
            asteroid* a = new asteroid();
            a->settings(sRock_small, 0, rand() % H, rand() % 360, 25);
            entities.push_back(a);
        }

        if (p->thrust)  p->anim = sPlayer_go;
        else   p->anim = sPlayer;

        for (auto i = entities.begin(); i != entities.end();)
        {
            Entity* e = *i;

            e->update();
            e->anim.update();

            if (e->life == false) { i = entities.erase(i); delete e; }
            else i++;
        }

        app.draw(fondo);
        for (auto i : entities) i->draw(app);
        app.display();
    }
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


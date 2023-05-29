// funcion main

#include <SFML/Graphics.hpp>

int main (){

    srand(time(0));
    RenderWindow app(VideoMode(W, H), "Astro crush");
    app.setFramerateLimit(60);
    
    //Texturas
    Texture t1,t2,t3,t4;
    t1.loadFromFile("images/Untitled5.png");
    t2.loadFromFile("images/fondo.png");
    t3.loadFromFile("images/Untitled4.png");
    t4.loadFromFile("images/Untitled7.png");

    t1.setSmooth(true);
    
    //Animaciones
    Animation sBullet(t3, 0,0,32,64, 16, 0.8);
    Animation sPlayer(t1, 40,0,40,40, 1, 0);
    Animation sPlayer_go(t1, 40,40,40,40, 1, 0);
    Animation sRock_small(t4, 0,0,64,64, 16, 0.2);

    std::list<Entity*> entities;

//Cantidad de asteroides que imprime 
    for(int i=0;i<3;i++)
    {
      asteroid *a = new asteroid();
      a->settings(sRock_small, rand()%W, rand()%H, rand()%360, 25);
      entities.push_back(a);
    }

    // posicion del jugador
    player *p = new player();
    p->settings(sPlayer,20,20,0,20);
    entities.push_back(p);

// main loop
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == Event::KeyPressed)
             if (event.key.code == Keyboard::Z)
              {
                bullet *b = new bullet();
                b->settings(sBullet,p->x,p->y,p->angle,10);
                entities.push_back(b);
              }
        }

//Controles
    if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle+=3;
    if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle-=3;
    if (Keyboard::isKeyPressed(Keyboard::Space)) p->thrust=true;
    else p->thrust=false;

//Si disparas un asteroide
     for(auto a:entities)
     for(auto b:entities)
     {
      if (a->name=="asteroid" && b->name=="bullet")
       if ( isCollide(a,b) )
           {
            a->life=false;
            b->life=false;

            Entity *e = new Entity();
            entities.push_back(e);


            for(int i=0;i<2;i++)
            {
             if (a->R==15) continue;
             Entity *e = new asteroid();
             e->settings(sRock_small,a->x,a->y,rand()%360,15);
             entities.push_back(e);
            }

           }
// Si chocas con un asteroide
       if (a->name=="player" && b->name=="asteroid")
       if ( isCollide(a,b) )
           {
            b->life=false;

            Entity *e = new Entity();
            entities.push_back(e);

            p->settings(sPlayer,20,20,0,20);
            p->dx=0; p->dy=0;
           }

     }


//La neta no se que hace este for, pero no le muevan
    if (rand()%500 == 0)
     {
       asteroid *a = new asteroid();
       a->settings(sRock_small, 0,rand()%H, rand()%360, 25);
       entities.push_back(a);
     }


    if (p->thrust)  p->anim = sPlayer_go;
    else   p->anim = sPlayer;

    for(auto i=entities.begin();i!=entities.end();)
    {
      Entity *e = *i;

      e->update();
      e->anim.update();

      if (e->life==false) {i=entities.erase(i); delete e;}
      else i++;
    }

        //draw
        app.clear();
        for(auto i:entities) i->draw(app);
        app.display();
    }

return 0;
}

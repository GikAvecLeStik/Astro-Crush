const int W = 1200;
const int H = 700;

float DEGTORAD = 0.017453f;

//--------------------------------------------------------------------------------------------------------------
class Animation
{
   public:
   float Frame, speed;
   Sprite sprite;
   Animation (Texture &t, int x, int y, int w, int h, int count, float Speed);
   void update();
   bool isEnd();


};
//--------------------------------------------------------------------------------------------------------------

class Entity
{
   public:
   float x,y,dx,dy,R,angle;
   bool life;
   std::string name;
   Animation anim;

   Entity();
   
   void settings(Animation &a,int X,int Y,float Angle=0,int radius=1);
 
   virtual void update(){};

   void draw(RenderWindow &app);
 
   virtual ~Entity(){};
};
//--------------------------------------------------------------------------------------------------------------

class asteroid: public Entity
{
   public:
   asteroid();
  

   void update();
  
};
//--------------------------------------------------------------------------------------------------------------
class player: public Entity
{
   public:
   bool thrust;

   player();

   void update();

};
//--------------------------------------------------------------------------------------------------------------

class bullet: public Entity
{
   public:
   bullet();
  

   void  update();
   

};
//--------------------------------------------------------------------------------------------------------------
bool isCollide(Entity *a,Entity *b);

//--------------------------------------------------------------------------------------------------------------

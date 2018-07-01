 const float radius_wheel=3.25;           //in cm
 const float pi =3.1416;
 float circum_wheel=2*pi*radius_wheel;
 const byte gear_teeth=12; 
 const int wheel_axis=15;
void setup()
{

}
void loop ()
{

}
void move_dist(float x,char y)
{float no_inter= (x/circum_wheel)*gear_teeth;
switch(y)
 {
case:'B': backward();break;                 //<=== using car functions for move
default: forward();break;
 }int k=0;
while (true)
  {
    if(digitalRead(photo_out)==1)    //let func is always high unless stop is called
    k++;
    if(k>=no_inter)
    {
      Stop();
      break;
    }             
  }
  void set_angle(float theta , char z)
  {
  /*
  float L = 0.5 * wheel_axis * theta ;      // Delta L  length of arc which the car move when its angel changes(L= r*theta).
  float no_inter= (L/circum_wheel)*gear_teeth ;   // number of inter
  switch(z)
 {
case:'L': Left();break;                 //<=== using car functions for move for angle clockwise or anti-clockwise
default: Right();break;
 }
 int k=0;
while (true)
  {
    if(digitalRead(photo_out)==1)    //let func is always high unless stop is called
    k++;
    if(k>=no_inter)
    {
      Stop();
      break;
    }             
   
  } */
}

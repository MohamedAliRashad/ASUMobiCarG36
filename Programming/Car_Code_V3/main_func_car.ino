# define sensor_out =9;
  const float pi =3.1416;
  const byte turn_inter= 12;             // no of interuptions for one turn of wheel
  const float wheel_rad = 3.0;         //wheel radius in cm         
  const byte rad_Of_rotation = 8;     //radius of rotation in cm (half of the car width)
void setup() {
  // put your setup code here, to run once:
pinMode (sensor_out,OUTPUT)
}

void loop() {
  // put your main code here, to run repeatedly:

}

void move_dist(int x,char u)                        // <==== x is input distance from user 
{ 
  int ini_dist=digitalRead(optical_out);
  int final_dist=ini_dist+x;                       // considering that sensor is having an inial value for distance
  float dist=0;
  int turns=0;
  int inter_no =0;
 while(!(dist<(final_dist+0.1*final_dist)&&dist>(final_dist-0.1*final_dist)))  // if dist =  final +or- 10% 
 {
     switch(u):
     case 'F' : forward ();break;                   //   <====== using built in functions in car
     case 'B' : backward ();break;  
     case 'R' : right ();break;                      //هنا الreading شكلها مش بتتاخدأثناء تنفيذ func forward
     case 'L' : left ();break; 
     default  : Stop ();break;  
     bool Read=digitalRead(optical_out);
    if(Read== HIGH)
    inter_no ++;                 
    if(inter_no==turn_inter)
    turns ++;
    dist=((float)inter_no/turn_inter)*2*pi*wheel_rad;
  }
   Stop ();
  }
  
 int abs_x(int x)            //  absolute func can be used for changing datatype`s referance for smaller ones when negative values are not reqired
  {if (x>0)
    return x;
    return x*(-1);}
    
   void set_angle(int x, char d)                    // for gyro using photo-interuptor
   {int turns=0;
    int inter_no =0;
    bool m = true ; 
   while(m)
    {     
    if(d==R)
     right ();
     else if (d==L)
     left ();  
    else if (d==R2)          //<=== right2 is a func for right around a wheel 
    right2();
    bool Read=digitalRead(optical_out);
    if(Read== HIGH)
    inter_no ++;                 
    if(inter_no==turn_inter)
    turns ++;
    float dist=((float)inter_no/turn_inter)*2*pi*wheel_rad;
    float alpha = (dist/rad_Of_rotation)*(180/pi);
    if (alpha<(x+0.1*x)&&alpha>(x-0.1*x))          // if alpha =  x +or- 10% can be reduced according to tolerance of sensor readings
    m = false;
    /*if(Read==LOW)
    {int session2=millis();}*/
      }
    } 
 void circle (char x,byte r)           //circle has 3 modes of operations:1==> around center axis ,2==> around a wheel ,3==> around arbitrary radius
 {
  if(x=='1'||)
  {set_angle(360,R);}
  if(x=='2')
  {set_angle(360,R2);}
  if(x=='3')
  {while()
  {
    float d_theta=
    }
   }
  else Stop();
  }
    }

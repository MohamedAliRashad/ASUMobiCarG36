/* YourDuino.com Example Software Sketch
 7-Way Robot Line Tracking Sensor Test
 http://arduino-info.wikispaces.com/Robot+7-wayMultiTrackingSensor
 terry@yourduino.com */

/*-----( Import needed libraries )-----*/

/*-----( Declare Constants )-----*/

/*-(Servo controls for Robot .. later)-*/
//#define MOTOR_LEFT 9  /*-(servo for Left wheel)-*/
//#define MOTOR_RIGHT 10 /*-(servo for Right wheel)-*/
//#define LEFT_ZERO_TRIM  0  
//#define RIGHT_ZERO_TRIM 2;  

/*-(Connections to NewWay 7-Way Robot Line Follower Sensor)-*/
#define SS1_LEFT_OUT  A5   
#define SS2_LEFT_IN   A4
#define SS3_CENTER    A3
#define CLP_BUMP      11
#define SS4_RIGHT_IN  A2
#define SS5_RIGHT_OUT A1  // Don't use pin 13 as an input..

#define NEAR          A0 // Used as digital, probably


/*-----( Declare objects )-----*/

/*-----( Declare Variables )-----*/

byte  LeftOut; 
byte  LeftIn;
byte  Center;
byte  RightIn;
byte  RightOut;

byte  Bump;
int   Near;  

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("YourDuino.com : 7-Way Sensor Test");
}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  Serial.println("Test Start");
  getSensorData();
  showSensorData();
  delay(1000);
}/* --(end main loop )-- */

/*-----( Declare User-written Functions )-----*/

void getSensorData()
{
  LeftOut  = analogRead(SS1_LEFT_OUT);  
  LeftIn   = analogRead(SS2_LEFT_IN);  
  Center   = analogRead(SS3_CENTER);  
  RightIn  = analogRead(SS4_RIGHT_IN); 
  RightOut = analogRead(SS5_RIGHT_OUT);  
  Bump     = digitalRead(CLP_BUMP);   
  Near     = analogRead(NEAR);     
}  

void showSensorData()
{
  Serial.print("L: ");Serial.println(LeftOut); 
  Serial.print("l: ");Serial.println(LeftIn);
  Serial.print("C: ");Serial.println(Center);
  Serial.print("r: ");Serial.println(RightIn);  
  Serial.print("R: ");Serial.println(RightOut); 
  //if (Bump     == 1) {Serial.print(" BUMP!");} else {Serial.print("      ");} 
  //if (Near) {Serial.print(Near);}  else {Serial.print("    ");}   
  Serial.println();
}  
/* ( THE END ) */


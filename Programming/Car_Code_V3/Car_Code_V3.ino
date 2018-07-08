//#include <PID_v1.h>
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(A2, A3); // RX, TX

#define radiusOfCar 8 // Half the width of the car
#define PI 3.1415926535897932384626433832795
#define circumference 18.849555  //in CM
#define ML_pinA 10
#define ML_pinB 9
#define MR_pinA 11
#define MR_pinB 5
#define SS1_LEFT_OUT  9
#define SS2_LEFT_IN   8
#define SS3_CENTER    7
#define SS4_RIGHT_IN  6
#define SS5_RIGHT_OUT A0 
#define Near A5
#define Cal 4
#define EncR 2
#define EncL 3
#define FeedBack A4

void allpinslow();
void Forward(int Speed);
void Backward(int Speed);
void Right(int Speed);
void Left(int Speed);
int GetData();
void Around(int SpeedL, int SpeedR);
void MoveFDist(int x);
void MoveBDist(int x);
void docountR();
void docountL();
void MoveAngle(int y);
void MoSquare(int side);
void MoInfinity(int Radius);
void MoRCircle(int Radius);
void MoLCircle(int Radius);
void MoSquare(int side);

//double SetPoint = 0, Input = 0, Output = 0;
char Data = 'S'; // the data received
unsigned int counterR=0;
unsigned int counterL=0;
unsigned int MaxSpeed = 127;
//char weights[5] = {0,-50,0,50,0};
//PID CarPID(&Input, &Output, &SetPoint,3,0,0,DIRECT);

void setup()
{
  pinMode(ML_pinA, OUTPUT);
  pinMode(ML_pinB, OUTPUT);
  pinMode(MR_pinA, OUTPUT);
  pinMode(MR_pinB, OUTPUT);
  pinMode(SS1_LEFT_OUT, INPUT);
  pinMode(SS2_LEFT_IN, INPUT);
  pinMode(SS3_CENTER, INPUT);
  pinMode(SS4_RIGHT_IN, INPUT);
  pinMode(SS5_RIGHT_OUT, INPUT);
  pinMode(Near, INPUT);
  pinMode(Cal, OUTPUT);
  pinMode(FeedBack, INPUT);
  pinMode(EncR, INPUT_PULLUP);
  pinMode(EncL, INPUT_PULLUP);
  
  //Initialization of all pin to be LOW
  allpinslow();

  //Initialzation of the PI
//  CarPID.SetMode(AUTOMATIC);

  //Setting Limits For the PID
  //CarPID.SetOutputLimits(-20, 20);

  //Install Bluetooth
  pinMode(A1, OUTPUT);
  digitalWrite(A1, HIGH);
  Bluetooth.begin(9600);
  Serial.begin(9600);

    //Command('S');
}

void loop() {

   
   if(digitalRead(Near)){
      Backward(MaxSpeed);
      delay(100);
      allpinslow();
      return;
    }


  if (Bluetooth.available()) //wait for data received
  { 
    Data=Bluetooth.read();
    if (Data)
        Command(Data);
  }

   
}

void Command(char Comm)
{
  switch(Comm)
  { 
  
    case 'M':
    while(1){
      if(Bluetooth.read() == 'm'){
        allpinslow();
        break;
      }

      if (digitalRead(SS2_LEFT_IN) == 0 && digitalRead(SS3_CENTER) == 1 && digitalRead(SS4_RIGHT_IN) == 0) {
            Forward(100);
      }

      else if (digitalRead(SS2_LEFT_IN) == 1  && digitalRead(SS4_RIGHT_IN) == 0) {
  
        while (!(digitalRead(SS3_CENTER) == 1)) {
            LeftSafe(100);
       }
     }
      else if (digitalRead(SS2_LEFT_IN) == 0 && digitalRead(SS4_RIGHT_IN) == 1) {

         while (!(digitalRead(SS3_CENTER) == 1)) {
           RightSafe(100);
          }
    
    }
    else{

        Forward(100);

    } 
  
    }

    case 'u':
    
    Around(100, 200);
    delay(10000);
    allpinslow();
    break;

    case 'f':    //Forward Automatic

    MoveFDist(GetData());

    break;

    case 'b':    //Backward Automatic

    MoveBDist(GetData());

    break;

    case 'a':    //Angle Automatic

    MoveAngle(GetData());

    break;

    case 's':    //Change Speed

    MaxSpeed = GetData();

    break;

    case 'q':    //Move square

    MoSquare(GetData());

    break;

    case 'r':    //Move Circle To the right

    MoRCircle(GetData());

    break;

    case 'l':    //Move Circle To the left

    MoLCircle(GetData());

    break;

    case 'i':    //Move Infinity Shape

    MoInfinity(GetData());

    break;

    case 'F':    //Forward Manual
 
    Forward(MaxSpeed);
    //Serial.println("Forward!");

    break;

    case 'G':    //Backward Manual
  
    Backward(MaxSpeed);
    //Serial.println("Backward!");
    break;
    
    case 'R':    //Right Manual
    
    Right(MaxSpeed);
    //Serial.println("Right!");
    break; 
    
    case 'L':    //Left Manual
  
    Left(MaxSpeed);

    break;     
    
    case 'S':
    
    allpinslow();
    
    break; 
  }
}

void allpinslow()
{
  digitalWrite(ML_pinA, LOW);
  digitalWrite(ML_pinB, LOW);
  digitalWrite(MR_pinA, LOW);
  digitalWrite(MR_pinB, LOW);
}

void Forward(int Speed) {

  analogWrite(ML_pinA, Speed);
  digitalWrite(ML_pinB, LOW);

  analogWrite(MR_pinA, Speed);
  digitalWrite(MR_pinB, LOW);

}
void Backward(int Speed) {

  digitalWrite(ML_pinA, LOW);
  analogWrite(ML_pinB, Speed);

  digitalWrite(MR_pinA, LOW);
  analogWrite(MR_pinB, Speed);


}
void Left(int Speed) {

  digitalWrite(ML_pinA, LOW);
  analogWrite(ML_pinB, Speed);

  analogWrite(MR_pinA, Speed);
  digitalWrite(MR_pinB, LOW);

}
void Right(int Speed) {

  analogWrite(ML_pinA, Speed);
  digitalWrite(ML_pinB, LOW);

  digitalWrite(MR_pinA, LOW);
  analogWrite(MR_pinB, Speed);

}
void LeftSafe(int Speed) {

  digitalWrite(ML_pinA, LOW);
  analogWrite(ML_pinB, LOW);

  analogWrite(MR_pinA, Speed);
  digitalWrite(MR_pinB, LOW);

}
void RightSafe(int Speed) {

  analogWrite(ML_pinA, Speed);
  digitalWrite(ML_pinB, LOW);

  digitalWrite(MR_pinA, LOW);
  digitalWrite(MR_pinB, LOW);

}

void Around(int SpeedL, int SpeedR) {

  analogWrite(ML_pinA, SpeedL);
  digitalWrite(ML_pinB, LOW);
  
  analogWrite(MR_pinA, SpeedR);
  digitalWrite(MR_pinB, LOW);
  

}

int GetData(){

  int Output = 0;
  char InArray[10];                    // Data will be held here as
  char count = 0;                     // Counting charcters received
  char data = Bluetooth.read();      // Data recieved From Bluetooth

  while(data != 'e' ){ 
  
    // Storing data from Bluetooth in an array
    if(data >= '0' && data <='9'){
      InArray[count] = data;
      count++;
    }
    data = Bluetooth.read();
  }

  // Transforming Charcters to integers
  for (char i = 0; i < count; i++){
        Output = Output + (InArray[i] - '0') * pow(10,count - i - 1);
  }
  if (Output >= 99)
      Output++;

  return Output;
}

void MoveFDist(int x){

  int NoInter = round((x/circumference) * 12);          // Transforming 

  attachInterrupt(digitalPinToInterrupt(EncR), docountR, RISING);
  //attachInterrupt(digitalPinToInterrupt(EncL), docountL, RISING);
  //if counterR < counterL 

  while (counterR < NoInter){
    Forward(MaxSpeed);
  }

  detachInterrupt(EncR);
  //detachInterrupt(EncL);

  counterR = 0;
  counterL = 0;
  
  allpinslow();
}


void MoveBDist(int x){

  int NoInter = round((x/circumference) * 12);          // Transforming 

  attachInterrupt(digitalPinToInterrupt(EncR), docountR, RISING);
  //attachInterrupt(digitalPinToInterrupt(EncL), docountL, RISING);
  //if counterR < counterL 

  while (counterR < NoInter){
    Backward(MaxSpeed);
  }

  detachInterrupt(EncR);
  //detachInterrupt(EncL);

  counterR = 0;
  counterL = 0;
  
  allpinslow();
}

void docountR()  // counts from the speed sensor
{
  counterR++;  // increase +1 the counter value
} 

void docountL()  // counts from the speed sensor
{
  counterL++;  // increase +1 the counter value
} 

void MoveAngle(int y){
 
  int NoInter = round(((y * PI/180) * radiusOfCar /circumference) * 12);

  attachInterrupt(digitalPinToInterrupt(EncR), docountR, FALLING);
  attachInterrupt(digitalPinToInterrupt(EncL), docountL, FALLING);
  //if counterR < counterL 

  while ((counterL + counterR) / 2 < NoInter){
    Right(MaxSpeed);
    //delay(10)
  }

  detachInterrupt(EncR);
  detachInterrupt(EncL);
  
  counterR = 0;
  counterL = 0;

  delay(25);
  allpinslow();
}

void MoSquare(int side){

  MoveFDist(side);
  delay(25);
  MoveAngle(90);
  delay(25);
  MoveFDist(side);
  delay(25);
  MoveAngle(90);
  delay(25);
  MoveFDist(side);
  delay(25);
  MoveAngle(90);
  delay(25);
  MoveFDist(side);
  delay(25);
  MoveAngle(90);
  
}

void MoRCircle(int Radius){

  int NoInter = round((2 * PI * (8 + Radius) / circumference ) * 12);

  attachInterrupt(digitalPinToInterrupt(EncL), docountL, FALLING);
  attachInterrupt(digitalPinToInterrupt(EncR), docountR, FALLING);
  
      while ((counterR + counterL) / 2 < NoInter){
        //Around(MaxSpeed, round(MaxSpeed * (Radius / (16 + Radius))));
        Around(200, 100);
      }

      detachInterrupt(EncL);
      detachInterrupt(EncR);

      counterR = 0;
      counterL = 0;
  
      allpinslow();

}

void MoLCircle(int Radius){


  int NoInter = round((2 * PI * (8 + Radius) / circumference ) * 12);

  attachInterrupt(digitalPinToInterrupt(EncL), docountL, FALLING);
  attachInterrupt(digitalPinToInterrupt(EncR), docountR, FALLING);
  
      while ((counterR + counterL) / 2 < NoInter){
        //Around(MaxSpeed, round(MaxSpeed * (Radius / (16 + Radius))));
        Around(100, 200);
      }

      detachInterrupt(EncL);
      detachInterrupt(EncR);

      counterR = 0;
      counterL = 0;
  
      allpinslow();
}

void MoInfinity(int Radius){

  MoRCircle(Radius);
  allpinslow();
  delay(10);
  MoLCircle(Radius);

}


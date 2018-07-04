#include <PID_v1.h>
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(A3, A2); // RX, TX

#define radiusOfCar 8 // Half the width of the car
#define circumference 20.41 //in CM
#define pi 3.1416
#define MaxSpeed 127
#define ML_pinA 9
#define ML_pinB 10
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

//double SetPoint = 0, Input = 0, Output = 0;
char Data = 'S'; // the data received
unsigned int counterR=0;
unsigned int counterL=0;
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
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
  Bluetooth.begin(9600);
}

void loop() {


   if(digitalRead(Near)){
      Backward(MaxSpeed);
      return;
    }

    Command('S');

  if (Bluetooth.available()) //wait for data received
  { 
    Data=Bluetooth.read();
    Command(Data);
  }

   
}

void Command(char Comm)
{
  switch(Comm)
  { 
  
    case 'M':
    while(Bluetooth.available()){
      
      if(Bluetooth.read() == 'm'){
        break;
      }

      if (digitalRead(SS2_LEFT_IN) == 1 && digitalRead(SS3_CENTER) == 0 && digitalRead(SS4_RIGHT_IN) == 1) {
        Forward(105);
      }

      else if (digitalRead(SS2_LEFT_IN) == 0  && digitalRead(SS4_RIGHT_IN) == 1) {
  
        while (!(digitalRead(SS3_CENTER) == 0)) {
        Left(95);
       }
     }
      else if (digitalRead(SS2_LEFT_IN) == 1 && digitalRead(SS4_RIGHT_IN) == 0) {

         while (!(digitalRead(SS3_CENTER) == 0)) {
           Right(95);
          }
    
    }
    else{

        Forward(105);

    } 
  
    }

    break;

    case 'f':

    MoveFDist(GetData);

    break;

    case 'b':

    MoveBDist(GetData);

    break;

    case 'a':

    MoveAngle(GetData);

    break;
    
    case 'F':    //Upper

    Forward(MaxSpeed);

    break;

    case 'G':    //Down
  
    Backward(MaxSpeed);

    break;
    
    case 'R':    //Right
    
    Right(MaxSpeed);

    break; 
    
    case 'L':    //Left
  
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

void MoveFDist(float x){

  int NoInter = (x/circumference) * 12;          // Transforming 

  attachInterrupt(digitalPinToInterrupt(EncR), docountR, RISING);
  //attachInterrupt(digitalPinToInterrupt(EncL), docountL, RISING);
  //if counterR < counterL 

  while (counterR < NoInter){
    Forward(MaxSpeed);
  }

  detachInterrupt(EncR);
  //detachInterrupt(EncL);

  allpinslow();
}


void MoveBDist(float x){

  int NoInter = (x/circumference) * 12;          // Transforming 

  attachInterrupt(digitalPinToInterrupt(EncR), docountR, RISING);
  //attachInterrupt(digitalPinToInterrupt(EncL), docountL, RISING);
  //if counterR < counterL 

  while (counterR < NoInter){
    Backward(MaxSpeed);
  }

  detachInterrupt(EncR);
  //detachInterrupt(EncL);

  allpinslow();
}

void docountR()  // counts from the speed sensor
{
  counterR++;  // increase +1 the counter value
} 

//void docountL()  // counts from the speed sensor
//{
//  counterL++;  // increase +1 the counter value
//} 

void MoveAngle(float y){
 
  int NoInter = ((y * pi/180) * radiusOfCar /circumference) * 12;

  attachInterrupt(digitalPinToInterrupt(EncR), docountR, RISING);
  //attachInterrupt(digitalPinToInterrupt(EncL), docountL, RISING);
  //if counterR < counterL 

  while (counterR < NoInter){
    Right(MaxSpeed);
  }

  detachInterrupt(EncR);
  //detachInterrupt(EncL);
  
  allpinslow();
}

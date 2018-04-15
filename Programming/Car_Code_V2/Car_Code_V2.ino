#include <PID_v1.h>
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(A3, A4); // RX, TX

#define MaxSpeed 127
#define ML_pinA 5
#define ML_pinB 9
#define MR_pinA 11
#define MR_pinB 10
#define SS1_LEFT_OUT  7
#define SS2_LEFT_IN   6
#define SS3_CENTER    4
#define SS4_RIGHT_IN  3
#define SS5_RIGHT_OUT 2 
#define Near A5
#define CLP 7

void allpinslow();
void Forward();
void Backward();
void Left();
void Right();
//double SetPoint = 0, Input = 0, Output = 0;
char Data = 'S'; // the data received
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
  pinMode(CLP, INPUT);
  
  //Initialization of all pin to be LOW
  allpinslow();

  //Initialization of the PID
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
      Backward();
      return;
    }

    //Command('S');

  // if (Bluetooth.available()) //wait for data received
  //{ 
    //Data=Bluetooth.read();
    //if(Data == 'M'){

      //while(1){
      
      //if(Bluetooth.read() == 'm'){
        //Data = 'S';
        //break;
      //}

     if (digitalRead(SS2_LEFT_IN) == 1 && digitalRead(SS3_CENTER) == 0 && digitalRead(SS4_RIGHT_IN) == 1){
       Forward();
       delay(20);
       //allpinslow();
       //delay(5);
     }
     else if(digitalRead(SS2_LEFT_IN) == 1  && digitalRead(SS4_RIGHT_IN) == 0){
       //Backward();
       //delay(5);
       Left();
       delay(5);
       //allpinslow();
       //delay(5);
     }
     else if(digitalRead(SS2_LEFT_IN) == 0 && digitalRead(SS4_RIGHT_IN) == 1){
       Right();
       delay(5);
       //allpinslow();
       //delay(5);
     }
    /* else if(digitalRead(SS2_LEFT_IN) == 1 && digitalRead(SS4_RIGHT_IN) == 1){
       Forward();
       //delay(5);
       //allpinslow();
       //delay(5);
     }
     */
     else{
      
       allpinslow();
     }


    //}

    //}
    //Command(Data);
  //}

   
}

void Command(char Comm)
{
  switch(Comm)
  { 
  /*
    case 'M':
    while(1){
      
      if(Bluetooth.read() == 'm'){
        break;
      }

      Input = (weights[1] * digitalRead(SS2_LEFT_IN) + weights[2] * digitalRead(SS3_CENTER) + weights[3] * digitalRead(SS4_RIGHT_IN)) / 3.0;
      CarPID.Compute();
      
      analogWrite(ML_pinA,MaxSpeed + Output);
      digitalWrite(ML_pinB,LOW);
    
      analogWrite(MR_pinA,MaxSpeed - Output);
      digitalWrite(MR_pinB,LOW);    
      
     if (digitalRead(SS2_LEFT_IN) == 0 & digitalRead(SS3_CENTER) == 1 & digitalRead(SS4_RIGHT_IN) == 0){

     }
    }
    break;
    */
    case 'F':    //Upper

    Forward();
    break;

    case 'G':    //Down
  
    Backward();
    break;
    
    case 'R':    //Right
    
    Right();
    break; 
    
    case 'L':    //Left
  
    Left();
    break;     
    
    case 'S':
    allpinslow();
    break; 
  }
}

void allpinslow()
{
  digitalWrite(ML_pinA,LOW);
  digitalWrite(ML_pinB,LOW);
  digitalWrite(MR_pinA,LOW);
  digitalWrite(MR_pinB,LOW);
}

void Forward(){

    analogWrite(ML_pinA,MaxSpeed);
    digitalWrite(ML_pinB,LOW);
    
    analogWrite(MR_pinA,MaxSpeed);
    digitalWrite(MR_pinB,LOW);    
    
}
void Backward(){
    
    digitalWrite(ML_pinA,LOW);
    analogWrite(ML_pinB,MaxSpeed);
    
    digitalWrite(MR_pinA,LOW);
    analogWrite(MR_pinB,MaxSpeed); 
    

}
void Right(){

    digitalWrite(ML_pinA,LOW);
    analogWrite(ML_pinB,2*MaxSpeed);
    
    analogWrite(MR_pinA,2*MaxSpeed);
    digitalWrite(MR_pinB,LOW); 
  
}
void Left(){
    analogWrite(ML_pinA,2*MaxSpeed);
    digitalWrite(ML_pinB,LOW);
    
    digitalWrite(MR_pinA,LOW);
    analogWrite(MR_pinB,2*MaxSpeed); 
  
}

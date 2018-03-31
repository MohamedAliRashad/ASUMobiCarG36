//Written by The Team


#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(A3, A4); // RX, TX

#define ML_pinA 5
#define ML_pinB 9
#define MR_pinA 11
#define MR_pinB 10
#define Near A5

char Data = 'S'; // the data received

void setup()
{
  pinMode(ML_pinA, OUTPUT);
  pinMode(ML_pinB, OUTPUT);
  pinMode(MR_pinA, OUTPUT);
  pinMode(MR_pinB, OUTPUT);
  
  //Initialization of all pin to be LOW
  allpinslow();

  //Install Bluetooth
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
  Bluetooth.begin(9600);
}

void loop() {

   if(digitalRead(Near)){
      Data = 'G';
      Command(Data);
      delay(1);
      allpinslow();
    }
    
   if (Bluetooth.available()) //wait for data received
  { 

    Bluetooth.print("AT+NAME=Team_36\r\n");
    Data=Bluetooth.read();
    Command(Data);
  }
  
}

void Command(char Comm)
{
  switch(Comm)
  {  
  case 'F':    //Upper
    analogWrite(ML_pinA,100);
    digitalWrite(ML_pinB,LOW);
    
    analogWrite(MR_pinA,100);
    digitalWrite(MR_pinB,LOW);    
    break;
  case 'G':    //Down
    digitalWrite(ML_pinA,LOW);
    analogWrite(ML_pinB,100);
    
    digitalWrite(MR_pinA,LOW);
    analogWrite(MR_pinB,100); 
    break;
  case 'R':    //Right
    digitalWrite(ML_pinA,LOW);
    digitalWrite(ML_pinB,LOW);
    
    analogWrite(MR_pinA,100);
    digitalWrite(MR_pinB,LOW); 
    break; 
  case 'L':    //Left
    analogWrite(ML_pinA,100);
    digitalWrite(ML_pinB,LOW);
    
    digitalWrite(MR_pinA,LOW);
    digitalWrite(MR_pinB,LOW); 
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


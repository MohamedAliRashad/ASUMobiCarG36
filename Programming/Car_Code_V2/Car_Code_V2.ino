//Written by The Team


#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(A3, A4); // RX, TX

#define M1_pinA 5
#define M1_pinB 9
#define M2_pinA 11
#define M2_pinB 10
#define Near A5

char Data = 'S'; // the data received

void setup()
{
  pinMode(M1_pinA, OUTPUT);
  pinMode(M1_pinB, OUTPUT);
  pinMode(M2_pinA, OUTPUT);
  pinMode(M2_pinB, OUTPUT);
  
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
    analogWrite(M1_pinA,100);
    digitalWrite(M1_pinB,LOW);
    
    analogWrite(M2_pinA,100);
    digitalWrite(M2_pinB,LOW);    
    break;
  case 'G':    //Down
    digitalWrite(M1_pinA,LOW);
    analogWrite(M1_pinB,100);
    
    digitalWrite(M2_pinA,LOW);
    analogWrite(M2_pinB,100); 
    break;
  case 'R':    //Right
    digitalWrite(M1_pinA,LOW);
    digitalWrite(M1_pinB,LOW);
    
    analogWrite(M2_pinA,100);
    digitalWrite(M2_pinB,LOW); 
    break; 
  case 'L':    //Left
    analogWrite(M1_pinA,100);
    digitalWrite(M1_pinB,LOW);
    
    digitalWrite(M2_pinA,LOW);
    digitalWrite(M2_pinB,LOW); 
    break;     
  case 'S':
    allpinslow();
    break; 
  }
}

void allpinslow()
{
  digitalWrite(M1_pinA,LOW);
  digitalWrite(M1_pinB,LOW);
  digitalWrite(M2_pinA,LOW);
  digitalWrite(M2_pinB,LOW);
}


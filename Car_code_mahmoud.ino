//Written by Mahmoud Gamal Deghadi
//27 Feb 2018
//Version 1

#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(A3, A4); // RX, TX

#define M1_pinA 9
#define M1_pinB 5
#define M2_pinA 11
#define M2_pinB 10
#define Near A5


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
  Serial.begin(9600);
}

void loop() {
  
  if (Bluetooth.available())//wait for data received
  { -+
    char Data; // the data received
    Bluetooth.print("AT+NAME=Team_36\r\n");
    Data=Bluetooth.read();
    if(digitalRead(Near))
      Data = 'N';
    Serial.write(Data);
    Command(Data);
  }
}

void Command(char Comm)
{
  switch(Comm)
  {  
  case 'U':    //Upper
    digitalWrite(M1_pinA,HIGH);
    digitalWrite(M1_pinB,LOW);
    
    digitalWrite(M2_pinA,HIGH);
    digitalWrite(M2_pinB,LOW);    
    break;
  case 'D':    //Down
    digitalWrite(M1_pinA,LOW);
    digitalWrite(M1_pinB,HIGH);
    
    digitalWrite(M2_pinA,LOW);
    digitalWrite(M2_pinB,HIGH); 
    break;
  case 'R':    //Right
    digitalWrite(M1_pinA,LOW);
    digitalWrite(M1_pinB,LOW);
    
    digitalWrite(M2_pinA,LOW);
    digitalWrite(M2_pinB,HIGH); 
    break; 
  case 'L':    //Left
    digitalWrite(M1_pinA,LOW);
    digitalWrite(M1_pinB,HIGH);
    
    digitalWrite(M2_pinA,LOW);
    digitalWrite(M2_pinB,LOW); 
    break;     
  case 'N':
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


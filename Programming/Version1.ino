
#define lmotorf 4 //Motor A1
#define lmotorb 5 //Motor A2
#define rmotorf 6 //Motor B1
#define rmotorb 7 //Motor B2

//HIGH white
//LOW black

void setup() {
pinMode(lmotorf,OUTPUT);
pinMode(rmotorf,OUTPUT);
pinMode(lmotorb,OUTPUT);
pinMode(rmotorb,OUTPUT);
pinMode(8,INPUT); 
pinMode(9,INPUT);
pinMode(10,INPUT);
pinMode(11,INPUT);
pinMode(12,INPUT);
pinMode(13,INPUT);
}

void loop() {

int sensor1=digitalRead(8);//sensor1
int sensor2=digitalRead(9);//sensor2
int sensor3=digitalRead(10);//sensor3
int sensor4=digitalRead(11);//sensor4
int sensor5=digitalRead(12);//sensor5

if((sensor2==LOW)&&(sensor3==LOW)&&(sensor4==LOW)) //When ALL ARE on WHITE line
{

digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}
else if((sensor2==HIGH)&&(sensor3==LOW)&&(sensor4==HIGH))

{ 
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}
else if((sensor2==LOW)&&(sensor3==HIGH)&&(sensor4==LOW))

{ 
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}
else if((sensor1==HIGH)&&(sensor5==LOW)&&(sensor2==LOW)&&(sensor3==HIGH)&&(sensor4==LOW))//1 LEFT

{ 
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}

else if((sensor1==LOW)&&(sensor5==HIGH)&&(sensor2==LOW)&&(sensor3==HIGH)&&(sensor4==HIGH))//1 LEFT

{ 
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}
else if((sensor1==HIGH)&&(sensor5==LOW)&&(sensor2==LOW)&&(sensor3==LOW)&&(sensor4==LOW))//1 LEFT

{ 
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}

else if((sensor1==LOW)&&(sensor5==HIGH)&&(sensor2==HIGH)&&(sensor3==HIGH)&&(sensor4==HIGH))//NULL

{ 
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}
else if((sensor2==LOW)&&(sensor3==LOW)&&(sensor4==HIGH))//1 LEFT

{ 
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}
else if((sensor2==LOW)&&(sensor3==HIGH)&&(sensor4==HIGH))//1 LEFT

{ 
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}

else if((sensor2==HIGH)&&(sensor3==LOW)&&(sensor4==LOW))//FOR RIGHT

{ 
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}

else if((sensor2==HIGH)&&(sensor3==HIGH)&&(sensor4==LOW))//FOR RIGHT

{ 
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}
else if((sensor1==HIGH)&&(sensor5==LOW)&&(sensor2==HIGH)&&(sensor3==HIGH)&&(sensor4==HIGH))//1 LEFT
{ 
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}
else if((sensor1==HIGH)&&(sensor5==LOW)&&(sensor2==HIGH)&&(sensor3==HIGH)&&(sensor4==LOW))//1 LEFT
{ 
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}

else if((sensor1==LOW)&&(sensor5==HIGH)&&(sensor2==LOW)&&(sensor3==HIGH)&&(sensor4==LOW))
{ 
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}
else if((sensor1==HIGH)&&(sensor5==LOW)&&(sensor2==HIGH)&&(sensor3==HIGH)&&(sensor4==HIGH))
{ 
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}

else if((sensor2==HIGH)&&(sensor3==HIGH)&&(sensor4==HIGH))//FOR RIGHT
{ 
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}
else
{
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}

}


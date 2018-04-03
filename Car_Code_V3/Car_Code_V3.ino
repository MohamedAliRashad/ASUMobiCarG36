
#define MaxSpeed 127 // Max Speed 50% Power
#define Kp 2
#define Kd 0
#define ML_pinA 5
#define ML_pinB 9
#define MR_pinA 11
#define MR_pinB 10
#define SS1_LEFT_OUT  6 
#define SS2_LEFT_IN   5
#define SS3_CENTER    4
#define SS4_RIGHT_IN  3
#define SS5_RIGHT_OUT 2
#define NEAR A5

char Weights[5] = {-10,-5, 0, 5, 10};
double Error = 0, LastError = 0;
char R, L, C;  //char Speed;
bool Flag = 0;  //Negative Sign
double Result;

void setup() {
  // put your setup code here, to run once:

  pinMode(ML_pinA, OUTPUT);
  pinMode(ML_pinB, OUTPUT);
  pinMode(MR_pinA, OUTPUT);
  pinMode(MR_pinB, OUTPUT);
  pinMode(SS1_LEFT_OUT, INPUT);
  pinMode(SS2_LEFT_IN, INPUT);
  pinMode(SS3_CENTER, INPUT);
  pinMode(SS4_RIGHT_IN, INPUT);
  pinMode(SS5_RIGHT_OUT, INPUT);
  pinMode(NEAR, INPUT);

  allpinslow();
}

void loop() {
  
  Flag = 0;
  
  // put your main code here, to run repeatedly
  L = Weights [0] * digitalRead(SS1_LEFT_OUT);
  l = Weights [1] * digitalRead(SS2_LEFT_IN);
  C = Weights [2] * digitalRead(SS3_CENTER);
  r = Weights [3] * digitalRead(SS4_RIGHT_IN);
  R = Weights [4] * digitalRead(SS5_RIGHT_OUT);
  
  Error = ( L + C + R) / 3;
  Result = Kp * Error + Kd * (Error - LastError);
  LastError = Error;
  if (Result <= 0){
    Result = -1 * Result;
    Flag = 1;
   } 

  if (Flag){
  analogWrite(MR_pinA, int(MaxSpeed/2 + Result/2));
  analogWrite(ML_pinA, int(MaxSpeed/2 - Result/2));
  digitalWrite(MR_pinB, LOW);
  digitalWrite(ML_pinB, LOW);
  }
  else{
  analogWrite(MR_pinA, int(MaxSpeed/2 - Result/2));
  analogWrite(ML_pinA, int(MaxSpeed/2 + Result/2));  
  digitalWrite(MR_pinB, LOW);
  digitalWrite(ML_pinB, LOW);
  }
}

void allpinslow()
{
  digitalWrite(ML_pinA,LOW);
  digitalWrite(ML_pinB,LOW);
  digitalWrite(MR_pinA,LOW);
  digitalWrite(MR_pinB,LOW);
}

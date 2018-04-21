#define Pwm 127
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
void Forward(int Speed);
void Backward(int Speed);
void Right(int Speed1, int Speed2);
void Left(int Speed1, int Speed2);
double PWMtoSpeed(int PWM);

unsigned long StartTime;
unsigned long CurrentTime;
unsigned long duration;
double distance;
double hypotenuse;
double RaidusOfCurvature;
double Ratio;
int Pwm2;
bool FLAG;

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

}

void loop() {


   if(digitalRead(Near)){
      Backward(Pwm);
      return;
    }
    
    Forward(Pwm);

    if(digitalRead(SS3_CENTER) == 1){
        StartTime = millis(); // We start the timing
        
        while(1){
            if(digitalRead(SS4_RIGHT_IN) == 0){
                CurrentTime = millis();
                FLAG = 1;
                break;
            }
            if(digitalRead(SS2_LEFT_IN) == 0){
                CurrentTime = millis();
                FLAG = 0;
                break;
            }
            Forward(Pwm);
        }
        duration = CurrentTime - StartTime; // The Duration of the white distance
        distance = PWMtoSpeed(Pwm) * duration; // The distance until the sensors go black
        hypotenuse = sqrt(pow(distance, 2) + pow(10, 2)); // getting the hypotenuse of the triangle
        RaidusOfCurvature = hypotenuse/0.087266; // The Raidus of the curve = the length of the curve which i approxmated to be the hypotenuse / The angle of the curve which i approxmated to be 5 degrees
        Ratio = (105 + RaidusOfCurvature) / (105 - RaidusOfCurvature); // The ratio between the speed of the motors
        Pwm2 = Ratio * Pwm; // Getting The others motor speed
        
        if(FLAG == 1)
        while(digitalRead(SS3_CENTER) == 1)
            Right(Pwm2, Pwm);
        else
        while(digitalRead(SS3_CENTER) == 1)
            Left(Pwm2, Pwm);

    } 
}

void allpinslow()
{
  digitalWrite(ML_pinA,LOW);
  digitalWrite(ML_pinB,LOW);
  digitalWrite(MR_pinA,LOW);
  digitalWrite(MR_pinB,LOW);
}

void Forward(int Speed)
{

    analogWrite(ML_pinA,Speed);
    digitalWrite(ML_pinB,LOW);
    
    analogWrite(MR_pinA,Speed);
    digitalWrite(MR_pinB,LOW);    
    
}
void Backward(int Speed)
{
    
    digitalWrite(ML_pinA,LOW);
    analogWrite(ML_pinB,Speed);
    
    digitalWrite(MR_pinA,LOW);
    analogWrite(MR_pinB,Speed); 
    

}
void Left(int Speed1, int Speed2 )
{

    digitalWrite(ML_pinA,LOW);
    analogWrite(ML_pinB,Speed1);
    
    analogWrite(MR_pinA,Speed2);
    digitalWrite(MR_pinB,LOW); 
  
}
void Right(int Speed1, int Speed2)
{

    analogWrite(ML_pinA,Speed1);
    digitalWrite(ML_pinB,LOW);
    
    digitalWrite(MR_pinA,LOW);
    analogWrite(MR_pinB,Speed2); 
  
}
double PWMtoSpeed(int PWM)
{

    return (13.8 * PWM + 73.86) * 0.01; //Speed in millimeters/milliseconds
    //return(-6.72 * pow(PWM,2) + 17.76 * PWM + 75.76)
    //return(1.28 * pow(PWM,3) - 7.081 * pow(PWM, 2) + 15.48 * PWM + 76.41)
    //return(-6.949 * pow(PWM, 4) + 4.308 * pow(PWM,3) - 6.281 * pow(PWM, 2) + 9.904 * PWM + 74.71)
    //return(10.66 * pow(PWM, 5) -6.949 * pow(PWM, 4) - 20.24 * pow(PWM,3) - 6.281 * pow(PWM, 2) + 09.89 * PWM + 74.71)
    
}


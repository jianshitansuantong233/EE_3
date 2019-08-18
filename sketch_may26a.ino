#define LED BLUE_LED
const int left_slp_pin=31; //must be HIGH to turn, DIGITAL
const int left_dir_pin=29;  //Direction , DIGITAL
const int left_pwm_pin=40; //ANALOG
const int right_slp_pin=11;
const int right_dir_pin=30;
const int right_pwm_pin=39;
const int EMITODD=45;
const int EMITEVEN=61;
const int REFL_0 = 65;
const int REFL_1 = 48;
const int REFL_2 = 64;
const int REFL_3 = 47;
const int REFL_4 = 52;
const int REFL_5 = 68;
const int REFL_6 = 53;
const int REFL_7 = 69;
const int ERA_maxticks = 12;
const int ELA_maxticks = 12;
double r0,r1,r2,r3,r4,r5,r6,r7; 
double sum,right,left,sum_1=0;
double speedA, speedL, speedR, adjustment;
double required=70; //About 1 cm/s
double diff, diff1, diff2;
int counter = 0;
const double kp=6;
const double kd=3;
double correct_value=0;
unsigned long currentTime, previousTime;
double elapsedTime;
double error, errorS, errorR, errorL;
double lastE=0, cumError, rateError;

void setup() {
  previousTime=millis();
  pinMode(left_slp_pin,OUTPUT);
  pinMode(left_dir_pin,OUTPUT);
  pinMode(left_pwm_pin,OUTPUT);
  pinMode(right_slp_pin,OUTPUT);
  pinMode(right_dir_pin,OUTPUT);
  pinMode(right_pwm_pin,OUTPUT);
  pinMode(EMITODD,OUTPUT);
  pinMode(EMITEVEN,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  digitalWrite(31,HIGH); //left
  digitalWrite(11,HIGH); //right motor
  digitalWrite(EMITODD,HIGH);
  digitalWrite(EMITEVEN,HIGH);
  pinMode(REFL_0, OUTPUT);
  pinMode(REFL_1, OUTPUT);
  pinMode(REFL_2, OUTPUT);
  pinMode(REFL_3, OUTPUT);
  pinMode(REFL_4, OUTPUT);
  pinMode(REFL_5, OUTPUT);
  pinMode(REFL_6, OUTPUT);
  pinMode(REFL_7, OUTPUT);
  digitalWrite(REFL_0,HIGH);
  digitalWrite(REFL_1,HIGH);
  digitalWrite(REFL_2,HIGH);
  digitalWrite(REFL_3,HIGH);
  digitalWrite(REFL_4,HIGH);
  digitalWrite(REFL_5,HIGH);
  digitalWrite(REFL_6,HIGH);
  digitalWrite(REFL_7,HIGH);
  delayMicroseconds(10);
  pinMode(REFL_0, INPUT);
  pinMode(REFL_1, INPUT);
  pinMode(REFL_2, INPUT);
  pinMode(REFL_3, INPUT);
  pinMode(REFL_4, INPUT);
  pinMode(REFL_5, INPUT);
  pinMode(REFL_6, INPUT);
  pinMode(REFL_7, INPUT);
  delayMicroseconds(1500);

  r0 = digitalRead(REFL_0); //right 
  r1 = digitalRead(REFL_1); 
  r2 = digitalRead(REFL_2);
  r3 = digitalRead(REFL_3);
  r4 = digitalRead(REFL_4);
  r5 = digitalRead(REFL_5);
  r6 = digitalRead(REFL_6);
  r7 = digitalRead(REFL_7); //left
  sum_1 = r0 + r1 + r2 + r3 + r4 + r5 + r6 + r7;
  sum = 1.75*r0 + 1.25 * r1 + .75* r2 + .25* r3 -.25* r4  -.75*r5  -1.25*r6  -1.75*r7;
  //Serial.println(sum_1);
  
  if(counter ==0){
    analogWrite(39,70);
    analogWrite(40,70);
    delay(100);
    counter++;
  }
  
  if( sum_1>6){//sum_1>6
    if ( counter == 1){
      required=35;
      digitalWrite(LED,HIGH);
      counter++;
      delay(100);
    }else if(counter==2){
      digitalWrite(LED,LOW);
      required=70;
     }
  }
 speedR = (ERA_maxticks*22)/(diff1*12); //divide by 12, multiply by 22 for cm/s
 speedL = (ELA_maxticks*22)/(diff2*12);
 errorR = required - speedR;
 errorL = required - speedL;
 adjustment = adjust();
 analogWrite(39, speedR +adjustment+errorR);
 analogWrite(40, speedL - adjustment+errorL);  //left
}

double adjust(){
  
  //errorR=required-RS;
  //errorL=required-LS;
  currentTime = millis();                //get current time
  elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation      
  error = correct_value - sum;                                // determine error
  rateError = (error - lastE)/elapsedTime;   // compute derivative
  double out = kp*error + kd*rateError;                //PID output               
  lastE = error;                                //remember current error
  previousTime = currentTime;                        //remember current time
  return out;           
 // return kp*error+ki*cumError+kd*rateError;  
}

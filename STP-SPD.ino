// STP-SPEED CONTROL
// This code is used to build bipolar stepper-motor control skills.
// Basic functions for writing to and operating the stepper motor are included;
// Half, Full, CW, and CCW functions are developed here and used in future
// code. This code is also used to control stepping speed (angular velocity).
// Adam Kotler, Fall 2020
//initialize pins
const int A_1=12;
const int A_2=3;
const int B_1=13;
const int B_2=11;
const int A_I=0;
const int B_I=1;
const int N=1;
const int S=2;
const int t=5000; // used to modify stepping speed


void setup() {
  //Coil A
  pinMode(A_1,OUTPUT);
  pinMode(A_2,OUTPUT);
  //Coil B
  pinMode(B_1,OUTPUT);
  pinMode(B_2,OUTPUT);
  pinMode(lim,INPUT_PULLUP);
  //Make sure all coils are off
  shutdown();
  //Start Serial Monitor
  Serial.begin(9600);
}

int T0=0;
int sum=0;
void loop() {
  T0=millis();
  for(int ct=1;ct<=50;ct++){ // Perform full step sequence; rotate 360 CCW
    FullCCW();
    sum+=4*1.5;
    Serial.println(String(millis()-T0)+"\t"+String(sum));
  }
  for(int ct=1;ct<=50;ct++){ // Perform full step sequence; rotate 360 CW
    FullCW();
    sum-=4*1.5;
    Serial.println(String(millis()-T0)+"\t"+String(sum));
  }
  shutdown();
  while(1);
}

//STEPPER CONTROL FUNCTIONS
//Function to turn off current to all coils
void shutdown(){
  digitalWrite(A_1,LOW);
  digitalWrite(A_2,LOW);
  digitalWrite(B_1,LOW);
  digitalWrite(B_2,LOW);
}

//CoilA control function
void contA(int pol){
  if(pol==N){
    digitalWrite(A_1,HIGH);
    digitalWrite(A_2,HIGH);
  }
  else if(pol==S){
    digitalWrite(A_1,LOW);
    digitalWrite(A_2,HIGH);
  }
  else{
   digitalWrite(A_1,LOW);
   digitalWrite(A_2,LOW);
  }
}

//CoilB control function
void contB(int pol){
  if(pol==N){
    digitalWrite(B_1,HIGH);
    digitalWrite(B_2,HIGH);
  }
  else if(pol==S){
    digitalWrite(B_1,LOW);
    digitalWrite(B_2,HIGH);
  }
  else{
   digitalWrite(B_1,LOW);
   digitalWrite(B_2,LOW);
  }
}

//4-step Full-step sequence; CCW
void FullCCW(){
    contA(N);
    contB(N);
    delayMicroseconds(t);
    
    contA(S);
    contB(N);
    delayMicroseconds(t);
 
    contA(S);
    contB(S);
    delayMicroseconds(t);

    contA(N);
    contB(S);
    delayMicroseconds(t);
}

//4-step Full-step sequence; CW
void FullCW(){
    contA(N);
    contB(S);
    delayMicroseconds(t);
    
    contA(S);
    contB(S);
    delayMicroseconds(t);
 
    contA(S);
    contB(N);
    delayMicroseconds(t);

    contA(N);
    contB(N);
    delayMicroseconds(t);
}

//8-step Half-step sequence; CCW
void HalfCCW(){

    contA(S);
    contB(N);
    delayMicroseconds(t);

    contA(S);
    contB(0);
    delayMicroseconds(t);

    contA(S);
    contB(S);
    delayMicroseconds(t);

    contA(0);
    contB(S);
    delayMicroseconds(t);

    contA(N);
    contB(S);
    delayMicroseconds(t);

    contA(N);
    contB(0);
    delayMicroseconds(t);

    contA(N);
    contB(N);
    delayMicroseconds(t);
    
    contA(0);
    contB(N);
    delayMicroseconds(t);
}

//8-step Half-step sequence; CW
void HalfCW(){
    contA(0);
    contB(N);
    delayMicroseconds(t);
    
    contA(N);
    contB(N);
    delayMicroseconds(t);
 
    contA(N);
    contB(0);
    delayMicroseconds(t);

    contA(N);
    contB(S);
    delayMicroseconds(t);

    contA(0);
    contB(S);
    delayMicroseconds(t);

    contA(S);
    contB(S);
    delayMicroseconds(t);

    contA(S);
    contB(0);
    delayMicroseconds(t);

    contA(S);
    contB(N);
    delayMicroseconds(t);
}

                                                                                                      

// STP-HOMING SEQUENCE
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
int t=1500;               // dynamic step-delay variable
const int lim=7;          // pin for momentary switch logic


void setup() {
  //Coil A
  pinMode(A_1,OUTPUT);
  pinMode(A_2,OUTPUT);
  //Coil B
  pinMode(B_1,OUTPUT);
  pinMode(B_2,OUTPUT);
  pinMode(lim,INPUT_PULLUP);    // Set switch to read from D7
  //Make sure all coils are off
  shutdown();
  //Start Serial Monitor
  Serial.begin(9600);
}

int T0=0;
int sum=0;
void loop() {
  //Home into momentary switch using full-cycle; initially full-cycle
  //to cover long distance
  while(digitalRead(lim)==HIGH){
    FullCCW();
  }
  t=3000;
  //Retract 10mm after hitting switch
  for(int ct=1;ct<=60;ct++){
    FullCW();
  }
  t=8000;
  //Re-home to switch using half-step cycle; Half-step cycle to
  //precisely home into switch "machine-zero"
  while(digitalRead(lim)==HIGH){
    HalfCCW();
  }
  t=1000;
  // After precision-homing, drive to any desired distance;
  // In my case, 600*4 full-steps is the far-limit of my linear-stage
  for(int ct=1;ct<=600;ct++){
    FullCW();
  }
  delay(1000);
  //Return to the center of the linear stage; ready for sequence restart
  for(int ct=1;ct<=450;ct++){
    FullCCW();
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
//
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

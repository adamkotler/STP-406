// STP-CURRENT MEASUREMENT
// This code is used to aid in developing knowledge of electro-mechanical
// function in stepper motors. Much of the code was provided by ME406
// professors. I made my own tweaks to better understand the workflow.
// Adam Kotler, Fall 2020
//initialize pins
int A_1=12;
int A_2=3;
int B_1=13;
int B_2=11;
int A_I=0;
int B_I=1;

void setup() {
  //Coil A
  pinMode(A_1,OUTPUT);
  pinMode(A_2,OUTPUT);
  //Coil B
  pinMode(B_1,OUTPUT);
  pinMode(B_2,OUTPUT);
  //Make sure all coils are off
  shutdown();
  //Start Serial Monitor
  Serial.begin(9600);
}

float iA=0, iB=0; // initialize current storage vars
int ct=0;
void loop() {
  //Apply Current to both coils
  digitalWrite(A_1,HIGH);
  digitalWrite(A_2,HIGH);
  digitalWrite(B_1,HIGH);
  digitalWrite(B_2,HIGH);
  //Store and print 20 times
  for (ct=0; ct<20; ct++){
    iA= float(analogRead(A_I)) /1023.0*5.0 / 1.65 * 1000.0;
    iB= float(analogRead(B_I)) /1023.0*5.0 / 1.65 * 1000.0;
    Serial.print("iA: ");
    Serial.print(iA);
    Serial.print(" | iB: ");
    Serial.println(iB);
  }
  shutdown(); //shutdown loop; avoid overheat
  while(1);   //stop looping
}

//Function to turn off current to all coils
void shutdown(){
  digitalWrite(A_1,LOW);
  digitalWrite(A_2,LOW);
  digitalWrite(B_1,LOW);
  digitalWrite(B_2,LOW);
}

#include <Wire.h>

#define SLAVE_ADDRESS 0x04
int L1Pin = 5;
int L2Pin = 6;
int R1Pin = 9;
int R2Pin = 10;

int L1;
int L2;
int R1;
int R2;
int state = 0;
int LState = 0;
int RState = 0;
int target = 0;
int val = 0;
void setup() {
  pinMode(13, OUTPUT);
  pinMode(L1Pin, OUTPUT);
  pinMode(L2Pin, OUTPUT);
  pinMode(R1Pin, OUTPUT);
  pinMode(R2Pin, OUTPUT);
  
  Serial.begin(9600); // start serial for output
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  
  Serial.println("Ready!");
}

void loop() {
  delay(100);
}

void setPinsSpeed(){
  analogWrite(L1Pin,L1);
  analogWrite(L2Pin,L2);
  analogWrite(R1Pin,R1);
  analogWrite(R2Pin,R2);
}

void readSpeed(){
  int cmd[4];
  int x = 0;
  while(Wire.available()) { //this line messed up
       cmd[x] = Wire.read();
       x++;
    Serial.print("cmd: ");
    Serial.println(cmd[x] );
  }
   Serial.print("count data: ");
    Serial.println(x);
  if ( x > 1 ) {
    target = 1;
   Serial.print("Set speed ");
    L1 = cmd[0];
    L2 = cmd[1];
    R1 = cmd[2];
    R2 = cmd[3];
    setPinsSpeed();
  } else {
    target = 2;
   Serial.print("Set single ");
   val = cmd[0];
   Serial.print("count data is still: ");
    Serial.println(x);
    
  }
}

bool changeTarget(){
   if (val>0 and val<4){
      target = val;
      Serial.print("target: ");
       Serial.println(target);
       return true;
   } else {
    return false;
   }
}

// callback for received data
void receiveData(int byteCount){

  if (Wire.available()) {
   // val = Wire.read();
    readSpeed();
    Serial.print("L1: ");
    Serial.println(L1);
    Serial.print("L2: ");
    Serial.println(L2);
    Serial.print("R1: ");
    Serial.println(R1);
    Serial.print("R2: ");
    Serial.println(R2);
 Serial.print("target: ");
    Serial.println(target);
 Serial.print("val: ");
    Serial.println(val);
  /*
   if ( changeTarget() == false) {
   
     if (target == 1){     
       LState = val;
     //  digitalWrite(L, LState); // set the LED on
       Serial.print("motor L: ");
       Serial.println(LState);
      } else
      if (target == 2){
        RState = val;
     //  digitalWrite(L, RState); // set the LED on
        Serial.print("motor R: ");
        Serial.println(RState);
      }
   }
    */

    
  }
}

// callback for sending data
void sendData(){
  Wire.write(R1);
}

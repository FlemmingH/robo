
typedef struct {
  int T;
  int L;
  int R; 
} directions;

directions dir[5];


int OnOffPin = 2;
int R1Pin = 5;
int R2Pin = 6;

int L1Pin = 9;
int L2Pin = 10;

int LSpeed = 255;
int RSpeed = 255; 

int doRun = 0;
bool runProgram = false;
int tick = 0;

unsigned long delayStart = 0; // the time the delay started
bool delayRunning = false; // true if still waiting for delay to finish

void setup() {
  pinMode(R1Pin, OUTPUT);
  pinMode(R2Pin, OUTPUT);
  pinMode(L1Pin, OUTPUT);
  pinMode(L2Pin, OUTPUT);
  Serial.begin(9600);         
  pinMode(OnOffPin, INPUT);

  delayStart = millis();
  delayRunning = true;

  dir[0].T = 3000;
  dir[0].L = 255;
  dir[0].R = 255;
  
  dir[1].T = 6000;
  dir[1].L = -255;
  dir[1].R = -128;
  
  dir[2].T = 12000;
  dir[2].L = 128;
  dir[2].R = 255;

  dir[3].T = 16000;
  dir[3].L = 255;
  dir[3].R = 255;

  dir[4].T = 18000;
  dir[4].L = 0;
  dir[4].R = 0;
}

void setSpeed() {
  Serial.print(RSpeed);
  Serial.print(" ");
  Serial.print(LSpeed);
  Serial.println(" ..");
  if (RSpeed >= 0) {
    analogWrite(R1Pin, RSpeed);
    analogWrite(R2Pin, 0);
  } else {
    analogWrite(R1Pin, 0);
    analogWrite(R2Pin, abs(RSpeed));
  }

  if (LSpeed >= 0) {
    analogWrite(L1Pin, LSpeed);
    analogWrite(L2Pin, 0);
  } else {
    Serial.print(abs(LSpeed));
    analogWrite(L1Pin, 0);
    analogWrite(L2Pin, abs(LSpeed));
  }

}

void getData() {
  int dTime = millis() - delayStart;
  Serial.println(" time: "+String(dTime));
  if ( delayRunning && (dTime >= dir[tick].T )) {
    RSpeed = dir[tick].R;
    LSpeed = dir[tick].L;
    tick += 1;
    if (tick > 4) delayRunning = false;
  }
}

void loop() {
  doRun = digitalRead(OnOffPin);
  if (doRun == HIGH) {
    runProgram = !runProgram;

    if (runProgram) {
      RSpeed = 255;
      tick = 0;
      delayStart = millis();
      delayRunning = true;
      getData();
    } else {
      RSpeed = 0;
      LSpeed = 0;
      setSpeed();
    }
    delay(1000); 
  }
  
  if (runProgram) {
    getData();
    setSpeed();
  }
}

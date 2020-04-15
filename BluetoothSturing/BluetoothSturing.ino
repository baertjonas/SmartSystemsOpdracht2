#include <ArduinoJson.h>
#include <SoftwareSerial.h>

const size_t capacity = JSON_OBJECT_SIZE(4) + 50;
DynamicJsonDocument doc(capacity);

const int RX = 0; //receive
const int TX = 1; //send
SoftwareSerial BTSerial(RX, TX); //nieuwe seriële connectie over bluetooth HC-05
        
const int motorLeft[] = {2,3}; //control pins left motor
const int motorRight[] = {8,9}; //control pins right motor
const int leftEnable = 5;
const int rightEnable = 6;
const int ledPin = 13;

uint8_t LeftSpeed;
int8_t LeftDir;
uint8_t RightSpeed;
int8_t RightDir;

String serialInput = "";
boolean newData = false;

void setup() {
  //Serial.begin(9600);
  //while (!Serial) continue;
  BTSerial.begin(9600);
  while (!BTSerial) continue;
  
  for (int i = 0; i < 2; i++) {
    pinMode(motorLeft[i], OUTPUT);
    pinMode(motorRight[i], OUTPUT);
  }
  pinMode(leftEnable, OUTPUT);
  pinMode(rightEnable, OUTPUT);
}

void loop() {
  while (BTSerial.available() > 0) {
    // read the incoming byte:
    serialInput = BTSerial.readStringUntil('\n');
    newData = true;
  }
  if (newData) {
    //deserializeJson
    deserializeJson(doc, serialInput);
    LeftSpeed = doc["LeftSpeed"]; // 255
    LeftDir = doc["LeftDir"]; // 1
    RightSpeed = doc["RightSpeed"]; // 255
    RightDir = doc["RightDir"]; // 1
    //BTSerial.print("Left speed: "); BTSerial.println(LeftSpeed);
    //BTSerial.print("Left direction: "); BTSerial.println(LeftDir);
    //BTSerial.print("Right speed: "); BTSerial.println(RightSpeed);
    //BTSerial.print("Right direction: "); BTSerial.println(RightDir);
    
    newData = false;    
  }

  analogWrite(leftEnable, LeftSpeed);
  SetLeftDir(LeftDir);
  analogWrite(rightEnable, RightSpeed);
  SetRightDir(RightDir);
}

void SetLeftDir(int8_t dir) {
  //Serial.println(LeftDir);
  if (dir == 1) {
    digitalWrite(motorLeft[0], HIGH);
    digitalWrite(motorLeft[1], LOW);
  } else if (dir == -1) {
    digitalWrite(motorLeft[0], LOW);
    digitalWrite(motorLeft[1], HIGH);
  } 
}

void SetRightDir(int8_t dir) {
  //Serial.println(ir);
  if (dir == 1) {
    digitalWrite(motorRight[0], HIGH);
    digitalWrite(motorRight[1], LOW);
  } else if (dir == -1) {
    digitalWrite(motorRight[0], LOW);
    digitalWrite(motorRight[1], HIGH);
  } 
}

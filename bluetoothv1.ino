#include<LiquidCrystal.h>
#include <Wire.h>

// Motor A connections
int enA = 11; //red wire
int in1 = A1; //green wire
int in2 = A2; //white wire
// Motor B connections
int enB = 3; //grey wire
int in3 = A3; //orange wire
int in4 = A0; //black wire
#define L_IR 2
#define R_IR 13

void setup() {

 pinMode(enA, OUTPUT);
 pinMode(enB, OUTPUT);
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);
 pinMode(in3, OUTPUT);
 pinMode(in4, OUTPUT);
 pinMode(L_IR,INPUT);
pinMode(R_IR,INPUT);

 digitalWrite(in1, LOW);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);

 Serial.begin(9600);
}

void loop() {

 if (Serial.available() > 0) {
 char inputvalue = char(Serial.read());

 if (inputvalue == 'F') {
 analogWrite(enA, 180);
 analogWrite(enB, 180);

 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
 }

 else if (inputvalue == 'B') {
 analogWrite(enA, 180);
 analogWrite(enB, 180);

 digitalWrite(in1, LOW);
 digitalWrite(in2, HIGH);
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 }

 else if (inputvalue == 'R') {
 analogWrite(enA, 130);
 analogWrite(enB, 255);

 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, HIGH);//HIGH
 digitalWrite(in4, LOW);
 }

 else if (inputvalue == 'L') {

 analogWrite(enA, 255);
 analogWrite(enB, 130);

 digitalWrite(in1, LOW);//HIGH
 digitalWrite(in2, HIGH);
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
 }

else if (inputvalue == 'C') {
      forward();
      while (Serial.available() == 0) {
        if (digitalRead(L_IR) == HIGH && digitalRead(R_IR) == HIGH) stop();
        if (digitalRead(L_IR) == HIGH && digitalRead(R_IR) == LOW) left();
        if (digitalRead(L_IR) == LOW && digitalRead(R_IR) == HIGH) right();
        if (digitalRead(L_IR) == LOW && digitalRead(R_IR) == LOW) forward();
      } }

 else if (inputvalue == 'A') {
  /* digitalWrite(in1, LOW);//HIGH
 digitalWrite(in2, HIGH);
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
 /*digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);*/
 stop();
 }

 else if (inputvalue == 'S') {
 digitalWrite(in1, LOW);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);
 }
 }
}

void forward(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enA,60);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(enB,60);
}

void left(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enA,150);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(enB,150);
}

void right(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enA,160);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enB,160);
}

void stop(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

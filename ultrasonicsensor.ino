#include <Adafruit_LiquidCrystal.h>

#define enA 11
#define IN1 A1
#define IN2 A2
#define IN3 A3
#define IN4 A0
#define enB 3

#define trigPin  1     
#define echoPin  10

float duration;

float distance = 0;


const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
Adafruit_LiquidCrystal lcd_1(rs,en, d4, d5, d6, d7);

void setup() {
  pinMode(enA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(enB,OUTPUT);

  pinMode(trigPin, OUTPUT);         
  pinMode(echoPin, INPUT);

  lcd_1.begin(16,2);
	lcd_1.print("Distance");

}

void loop() {


  lcd_1.setCursor(0, 1);
  lcd_1.setBacklight(1);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);     
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2; 
  delay(10);
  lcd_1.setCursor(0, 1);
  lcd_1.print(distance);


  if (distance>50) forward();
  else stop();
  
}

void forward(){
 digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(enA, 70);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(enB, 70);
}

void left(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(enA,250);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(enB,200);
}

void right(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(enA,250);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(enB,200);
}

void stop(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}


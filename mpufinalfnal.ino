#include <Adafruit_LiquidCrystal.h>
#include <Wire.h>

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

int angle;
double y;

#define enA 11
#define IN1 A1
#define IN2 A2
#define IN3 A3
#define IN4 A0
#define enB 3

#define L_IR 2
#define R_IR 13

#define LRE 12
float distance = 0;
int counter = 0;
int latest = 0;

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
Adafruit_LiquidCrystal lcd_1(rs, en, d4, d5, d6, d7);
float seconds = 0;
int start = 0;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(L_IR, INPUT);
  pinMode(R_IR, INPUT);

  pinMode(LRE, INPUT);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  lcd_1.begin(16, 2);
  lcd_1.print("Angle:");
  start = 0; // Initialize 'start' variable
}

void loop() {
  lcd_1.setCursor(0, 1);
  lcd_1.print("Time:");
  lcd_1.setCursor(6, 1);
  lcd_1.print(seconds);
  delay(100);
  seconds += 0.1;
  measureAngle();

  if (angle >= 250 && angle <= 360) {
    lcd_1.setCursor(8, 0);
    lcd_1.print("0");
  } else {
    lcd_1.setCursor(8, 0);
    lcd_1.print(angle);
  }

  task1();
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(enA, 100);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(enB, 100);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(enA, 250);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(enB, 250);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(enA, 250);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(enB, 250);
}

void threesixty() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(enA, 210);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(enB, 210);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void countDistance() {
  int encoder = digitalRead(LRE);

  if (encoder != latest) {
    if (encoder == HIGH) counter++;
  }

  latest = encoder;

  distance = ((float)20.42 / 20) * (float)counter;
}

void measureAngle() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);

  angle = static_cast<int>(y + 0.5);
}

void task1() {
  if (seconds <= 3.5) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(enA, 110);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(enB, 110);
  } else if (seconds > 3.5) {
    if (angle > 300 || angle < 10) stop();
  } else if (seconds > 6.5 && seconds <= 7.9) {
    threesixty();
  } else if (seconds > 7.9 && seconds <= 9) {
    forward();
  } else if (seconds >= 9) {
    if (angle > 300 || angle < 10) {
      countDistance();
      lcd_1.clear();
      lcd_1.setCursor(0, 0);
      lcd_1.print("Distance:");
      lcd_1.setCursor(10, 0);
      lcd_1.print(distance);

      if (distance >= 200 && distance < 210) {
        stop();
        delay(3000);
        start = 1;
      }

      while (start == 1) {
        countDistance();
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Distance:");
        lcd_1.setCursor(10, 0);
        lcd_1.print(distance);

        if (digitalRead(L_IR) == HIGH && digitalRead(R_IR) == HIGH) stop();
        if (digitalRead(L_IR) == HIGH && digitalRead(R_IR) == LOW) left();
        if (digitalRead(L_IR) == LOW && digitalRead(R_IR) == HIGH) right();
        if (digitalRead(L_IR) == LOW && digitalRead(R_IR) == LOW) forward();
      }
    }
  }
}

#define LeftPWM 9
#define LeftIN1 7
#define LeftIN2 8
#define RightPWM 10
#define RightIN1 12
#define RightIN2 11
float speed = 75;

int State;

#define Sens1 A0
float MinS1 = 0;
float MaxS1 = 1024;
#define Sens2 A1
float MinS2 = 0;
float MaxS2 = 1024;
#define Sens3 A2
float MinS3 = 0;
float MaxS3 = 1024;
#define Sens4 A3
float MinS4 = 0;
float MaxS4 = 1024;
#define Sens5 A4
float MinS5 = 0;
float MaxS5 = 1024;
#define Sens6 A5
float MinS6 = 1024;
float MaxS6 = 0;
#define Sens7 A6
float MinS7 = 0;
float MaxS7 = 1024;
#define Sens8 A7
float MinS8 = 0;
float MaxS8 = 1024;

float kP = 0.75;
float kI = 0;
float kD = 10;

void setup() {
  pinMode(LeftPWM, OUTPUT);
  pinMode(LeftIN1, OUTPUT);
  pinMode(LeftIN2, OUTPUT);
  pinMode(RightPWM, OUTPUT);
  pinMode(RightIN1, OUTPUT);
  pinMode(RightIN2, OUTPUT);
  Serial.begin(9600);

  pinMode(2, INPUT);
}

float I = 0;
float LE = 0;
float PID(float error) {
  float P = error;
  I = I * (2 / 3) + error;
  float D = error - LE;
  Serial.println(D);
  LE = error;
  return (P * kP + I * kI + D * kD);
}
float sensor() {
  float W1 = -100;
  float W2 = -75;
  float W3 = -50;
  float W4 = -25;
  float W5 = 25;
  float W6 = 50;
  float W7 = 75;
  float W8 = 100;
  float Sensor1 = analogRead(Sens1);//map(analogRead(Sens1), MinS1, MaxS1, 0, 100);
  float Sensor2 = analogRead(Sens2);//map(analogRead(Sens2), MinS2, MaxS2, 0, 100);
  float Sensor3 = analogRead(Sens3);//map(analogRead(Sens3), MinS3, MaxS3, 0, 100);
  float Sensor4 = analogRead(Sens4);//map(analogRead(Sens4), MinS4, MaxS4, 0, 100);
  float Sensor5 = analogRead(Sens5);//map(analogRead(Sens5), MinS5, MaxS5, 0, 100);
  float Sensor6 = analogRead(Sens6);//map(analogRead(Sens6), MinS6, MaxS6, 0, 100);
  float Sensor7 = analogRead(Sens7);//map(analogRead(Sens7), MinS7, MaxS7, 0, 100);
  float Sensor8 = analogRead(Sens8);//map(analogRead(Sens8), MinS8, MaxS8, 0, 100);
  /*Serial.print(Sensor1);
  Serial.print(" ");
  Serial.print(Sensor2);
  Serial.print(" ");
  Serial.print(Sensor3);
  Serial.print(" ");
  Serial.print(Sensor4);
  Serial.print(" ");
  Serial.print(Sensor5);
  Serial.print(" ");
  Serial.print(Sensor6);
  Serial.print(" ");
  Serial.print(Sensor7);
  Serial.print(" ");
  Serial.print(Sensor8);
  Serial.println(" ");*/
  
  return ((Sensor1 * W1 + Sensor2 * W2 + Sensor3 * W3 + Sensor4 * W4 + Sensor5 * W5 + Sensor6 * W6 + Sensor7 * W7 + Sensor8 * W8) / (Sensor1 + Sensor2 + Sensor3 + Sensor4 + Sensor5 + Sensor6 + Sensor7 + Sensor8));
}

void Drive(float error) {
  float left = speed - error;
  float right = speed + error;
  /*Serial.print(error);
  Serial.print(" ");
  Serial.print(left);
  Serial.print(" ");
  Serial.print(right);
  Serial.println(" ");
  */
  if (right < 1) {
    digitalWrite(RightIN1, 1);
    digitalWrite(RightIN2, 1);
  } else {
    digitalWrite(RightIN1, 1);
    digitalWrite(RightIN2, 0);
  }
  if (left < 1) {
    digitalWrite(LeftIN1, 1);
    digitalWrite(LeftIN2, 1);
  } else {
    digitalWrite(LeftIN1, 1);
    digitalWrite(LeftIN2, 0);
  }
  if (left > 100) {
    left / max(left, right) * 100;
  }
  if (right > 100) {
    right / max(left, right) * 100;
  }
  left = map(left, 0, 100, 0, 255);
  right = map(right, 0, 100, 0, 255);
  analogWrite(RightPWM, right);
  analogWrite(LeftPWM, left);
  
}

void calibrate () {
  digitalWrite(LeftIN1, HIGH);
  digitalWrite(LeftIN2, LOW);
  analogWrite(LeftPWM, 125);

  digitalWrite(RightIN1, LOW);
  digitalWrite(RightIN2, HIGH);
  analogWrite(RightPWM, 125);

  if (MaxS1 < analogRead(Sens1)) {
    MaxS1 = analogRead(Sens1);
  }
  if (MinS1 > analogRead(Sens1)) {
    MinS1 = analogRead(Sens1);
  }

  if (MaxS2 < analogRead(Sens2)) {
    MaxS2 = analogRead(Sens2);
  }
  if (MinS2 > analogRead(Sens2)) {
    MinS2 = analogRead(Sens2);
  }

  if (MaxS3 < analogRead(Sens3)) {
    MaxS3 = analogRead(Sens3);
  }
  if (MinS3 > analogRead(Sens3)) {
    MinS3 = analogRead(Sens3);
  }

  if (MaxS4 < analogRead(Sens4)) {
    MaxS4 = analogRead(Sens4);
  }
  if (MinS4 > analogRead(Sens4)) {
    MinS4 = analogRead(Sens4);
  }

  if (MaxS5 < analogRead(Sens5)) {
    MaxS5 = analogRead(Sens5);
  }
  if (MinS5 > analogRead(Sens5)) {
    MinS5 = analogRead(Sens5);
  }

  if (MaxS6 < analogRead(Sens6)) {
    MaxS6 = analogRead(Sens6);
  }
  if (MinS6 > analogRead(Sens6)) {
    MinS6 = analogRead(Sens6);
  }

  if (MaxS7 < analogRead(Sens7)) {
    MaxS7 = analogRead(Sens7);
  }
  if (MinS7 > analogRead(Sens7)) {
    MinS7 = analogRead(Sens7);
  }

  if (MaxS8 < analogRead(Sens8)) {
    MaxS8 = analogRead(Sens8);
  }
  if (MinS8 > analogRead(Sens8)) {
    MinS8 = analogRead(Sens8);
  }

}


void loop() {
  State = digitalRead(2);
  if (State == 1) {
    calibrate();
  } else {
    Drive(PID(sensor()));
  }
}

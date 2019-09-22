#define MYDEBUG 

#define MOTORS
#define LeftPWM 9
#define LeftIN1 7
#define LeftIN2 8
#define RightPWM 10
#define RightIN1 12
#define RightIN2 11
float speed = 58;

float calibrT = millis();

int State;

#define Sens1 A0
float MinS1 = 1024;
float MaxS1 = 0;
#define Sens2 A1
float MinS2 = 1024;
float MaxS2 = 0;
#define Sens3 A2
float MinS3 = 1024;
float MaxS3 = 0;
#define Sens4 A3
float MinS4 = 1024;
float MaxS4 = 0;
#define Sens5 A4
float MinS5 = 1024;
float MaxS5 = 0;
#define Sens6 A5
float MinS6 = 1024;
float MaxS6 = 0;
#define Sens7 A6
float MinS7 = 1024;
float MaxS7 = 0;
#define Sens8 A7
float MinS8 = 1024;
float MaxS8 = 0;

float kP = 0.4;
float kI = 0;
float kD = 700;

void setup() {
  pinMode(LeftPWM, OUTPUT);
  pinMode(LeftIN1, OUTPUT);
  pinMode(LeftIN2, OUTPUT);
  pinMode(RightPWM, OUTPUT);
  pinMode(RightIN1, OUTPUT);
  pinMode(RightIN2, OUTPUT);
  Serial.begin(9600);
  Serial.println("1");
  pinMode(2, INPUT);
}

void log(String text) {
  #ifdef MYDEBUG
    Serial.print(text);
  #endif
}
float error_global;
float I = 0;
float LE = 0;
float prevT = micros();
float PID(float error) {
  error_global = error;
  float P = error;
  I = I * (2.0 / 3.0) + error;
  float dT = (micros() - prevT) / 1000.0;
  float D = (error - LE) / dT;
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

  float Sensor1 = map(analogRead(Sens1), MinS1, MaxS1, 0, 100);
  float Sensor2 = map(analogRead(Sens2), MinS2, MaxS2, 0, 100);
  float Sensor3 = map(analogRead(Sens3), MinS3, MaxS3, 0, 100);
  float Sensor4 = map(analogRead(Sens4), MinS4, MaxS4, 0, 100);
  float Sensor5 = map(analogRead(Sens5), MinS5, MaxS5, 0, 100);
  float Sensor6 = map(analogRead(Sens6), MinS6, MaxS6, 0, 100);
  float Sensor7 = map(analogRead(Sens7), MinS7, MaxS7, 0, 100);
  float Sensor8 = map(analogRead(Sens8), MinS8, MaxS8, 0, 100);
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
  float Sensor1 = map(analogRead(Sens1), MinS1, MaxS1, 0, 100);
  float Sensor2 = map(analogRead(Sens2), MinS2, MaxS2, 0, 100);
  float Sensor3 = map(analogRead(Sens3), MinS3, MaxS3, 0, 100);
  float Sensor4 = map(analogRead(Sens4), MinS4, MaxS4, 0, 100);
  float Sensor5 = map(analogRead(Sens5), MinS5, MaxS5, 0, 100);
  float Sensor6 = map(analogRead(Sens6), MinS6, MaxS6, 0, 100);
  float Sensor7 = map(analogRead(Sens7), MinS7, MaxS7, 0, 100);
  float Sensor8 = map(analogRead(Sens8), MinS8, MaxS8, 0, 100);
  if (Sensor1 < 50 && Sensor2 < 50 && Sensor3 < 50 && Sensor4 < 50 && Sensor5 < 50 && Sensor6 < 50 && Sensor7 < 50 && Sensor8 < 50) {
    
    if (LE < 0) {
      while(Sensor1 < 50 && Sensor2 < 50 && Sensor3 < 50 && Sensor4 < 50 && Sensor5 < 50 && Sensor6 < 50 && Sensor7 < 50 && Sensor8 < 50) {
         Sensor1 = map(analogRead(Sens1), MinS1, MaxS1, 0, 100);
         Sensor2 = map(analogRead(Sens2), MinS2, MaxS2, 0, 100);
         Sensor3 = map(analogRead(Sens3), MinS3, MaxS3, 0, 100);
         Sensor4 = map(analogRead(Sens4), MinS4, MaxS4, 0, 100);
         Sensor5 = map(analogRead(Sens5), MinS5, MaxS5, 0, 100);
         Sensor6 = map(analogRead(Sens6), MinS6, MaxS6, 0, 100);
         Sensor7 = map(analogRead(Sens7), MinS7, MaxS7, 0, 100);
         Sensor8 = map(analogRead(Sens8), MinS8, MaxS8, 0, 100);
        analogWrite(LeftPWM,map(speed,0,100,0,255)); 
        digitalWrite(LeftIN1,1);
        digitalWrite(LeftIN2,0);
        digitalWrite(RightIN1,1);
        digitalWrite(RightIN2,1);
        analogWrite(RightPWM,map(20 ,0,100,0,255));
        //delay(100);
      }
      
    
    }
    if (LE > 0) {
      while(Sensor1 < 50 && Sensor2 < 50 && Sensor3 < 50 && Sensor4 < 50 && Sensor5 < 50 && Sensor6 < 50 && Sensor7 < 50 && Sensor8 < 50) {
        Sensor1 = map(analogRead(Sens1), MinS1, MaxS1, 0, 100);
         Sensor2 = map(analogRead(Sens2), MinS2, MaxS2, 0, 100);
         Sensor3 = map(analogRead(Sens3), MinS3, MaxS3, 0, 100);
         Sensor4 = map(analogRead(Sens4), MinS4, MaxS4, 0, 100);
         Sensor5 = map(analogRead(Sens5), MinS5, MaxS5, 0, 100);
         Sensor6 = map(analogRead(Sens6), MinS6, MaxS6, 0, 100);
         Sensor7 = map(analogRead(Sens7), MinS7, MaxS7, 0, 100);
         Sensor8 = map(analogRead(Sens8), MinS8, MaxS8, 0, 100);
        analogWrite(RightPWM,map(speed ,0,100,0,255));
        digitalWrite(RightIN1,1);
        digitalWrite(RightIN2,0);
        digitalWrite(LeftIN1,0);
        analogWrite(LeftPWM,map(20 ,0,100,0,255));
        digitalWrite(LeftIN2,1);
        //delay(100);
      }
      
    
    }
  } else {
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
    left = left / max(left, right) * 100;
    right = right / max(left, right) * 100;
  }
  if (right > 100) {
    left = left / max(left, right) * 100;
    right = right / max(left, right) * 100;
  }
  left = map(left, 0, 100, 0, 255);
  right = map(right, 0, 100, 0, 255);
  #ifdef MOTORS
    log("2");      
    analogWrite(RightPWM, right);
    analogWrite(LeftPWM, left);
  #endif
  }
  
}

void calibrate () {
  #ifdef MOTORS
    digitalWrite(LeftIN1, HIGH);
    digitalWrite(LeftIN2, LOW);
    analogWrite(LeftPWM, 50);

    digitalWrite(RightIN1, LOW);
    digitalWrite(RightIN2, HIGH);
    analogWrite(RightPWM, 50);
  #endif
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
    if (millis() - calibrT < 2500) {
      calibrate();
    } else {
      digitalWrite(LeftIN1, 1);
      digitalWrite(LeftIN2, 1);
      digitalWrite(RightIN1, 1);
      digitalWrite(RightIN2, 1);
    }
    LE = 0;
    I = 0; 
  } else {
    Drive(PID(sensor()));
    LE = error_global;
  }
}

#include <Servo.h>
#include <AFMotor.h>

#define Echo A0
#define Trig A1
#define motor 10
#define Speed 170
#define spoint 103

char value;
int distance;

Servo servo;
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);

void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  servo.attach(motor);
  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);
}

int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2;
  return cm;
}

void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void right() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void left() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}

int leftsee() {
  servo.write(180);
  delay(800);
  int Right = ultrasonic();
  return Right;
}

int rightsee() {
  servo.write(20);
  delay(800);
  int Left = ultrasonic();
  return Left;
}

void Bluetoothcontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
  }
  if (value == 'F') {
    forward();
  } else if (value == 'B') {
    backward();
  } else if (value == 'L') {
    left();
  } else if (value == 'R') {
    right();
  } else if (value == 'S') {
    Stop();
  }
}


void Obstacle() {
  distance = ultrasonic();
  if (distance <= 14) {
    Stop();
    backward();
    delay(100);
    Stop();

    int L = leftsee();
    servo.write(spoint);
    delay(800);
    int R = rightsee();
    servo.write(spoint);

    if (L < R) {
      right();
      delay(500);
      Stop();
      delay(200);
    } else {
      left();
      delay(500);
      Stop();
      delay(200);
    }
  } else {
    forward();
  }
}

void EmergencyStop() {
  Bluetoothcontrol(); // Call standard Bluetooth control
    distance = ultrasonic();
 if (distance <= 16) {
    Stop();
    backward();
    delay(50);
    Stop();
  }
  else {
    forward();
  }
}

void BluetoothcontrolandObstacle() {
  Bluetoothcontrol(); // Call standard Bluetooth control
  Obstacle(); // Call to detect obstacle and turn only
}


void loop() {
  if (Serial.available() > 0) {
    value = Serial.read();
  }

  switch (value) {
    case 'A':
      Bluetoothcontrol();
      break;
    case 'O':
      EmergencyStop();
      break;
    case 'T':
      BluetoothcontrolandObstacle();
      break;
    case 'X':
      Stop();
      break;
    default:
      Bluetoothcontrol();
      break;
  }
}
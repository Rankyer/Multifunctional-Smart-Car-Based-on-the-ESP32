//turn left代表向左平移，left代表向左自旋

#define motorA1 15 
#define motorA2 2
#define motorB1 4 
#define motorB2 16
#define motorC1 17 
#define motorC2 5
#define motorD1 18 
#define motorD2 19
/////////////////////
//定义传感器
const int pin34 = 34;
const int pin35 = 35;
const int pin33 = 33;
const int pin25 = 25;

//////////////////////////////////
// 控制电机前进moveForward
void moveBackward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  digitalWrite(motorC1, HIGH);
  digitalWrite(motorC2, LOW);
  digitalWrite(motorD1, HIGH);
  digitalWrite(motorD2, LOW);
}

// 控制电机后退
void moveForward() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  digitalWrite(motorC1, LOW);
  digitalWrite(motorC2, HIGH);
  digitalWrite(motorD1, LOW);
  digitalWrite(motorD2, HIGH);
}

// // 控制电机左转
// void turnLeft() {
//   digitalWrite(motorA1, LOW);
//   digitalWrite(motorA2, HIGH);
//   digitalWrite(motorB1, HIGH);
//   digitalWrite(motorB2, LOW);
//   digitalWrite(motorC1, HIGH);
//   digitalWrite(motorC2, LOW);
//   digitalWrite(motorD1, LOW);
//   digitalWrite(motorD2, HIGH);
// }

// // 控制电机右转
// void turnRight() {
//   digitalWrite(motorA1, HIGH);
//   digitalWrite(motorA2, LOW);
//   digitalWrite(motorB1, LOW);
//   digitalWrite(motorB2, HIGH);
//   digitalWrite(motorC1, LOW);
//   digitalWrite(motorC2, HIGH);
//   digitalWrite(motorD1, HIGH);
//   digitalWrite(motorD2, LOW);
// }



void right() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  digitalWrite(motorC1, HIGH);
  digitalWrite(motorC2, LOW);
  digitalWrite(motorD1, HIGH);
  digitalWrite(motorD2, LOW);
}

//stop
void stop(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  digitalWrite(motorC1, LOW);
  digitalWrite(motorC2, LOW);
  digitalWrite(motorD1, LOW);
  digitalWrite(motorD2, LOW);
}



void left() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  digitalWrite(motorC1, LOW);
  digitalWrite(motorC2, HIGH);
  digitalWrite(motorD1, HIGH);
  digitalWrite(motorD2, LOW);
}

//////////////////////////////////

void setup() {

  pinMode(pin34, INPUT);
  pinMode(pin35, INPUT);
  pinMode(pin33, INPUT);
  pinMode(pin25, INPUT);
////////////////////////////////////////////////////////
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(motorC1, OUTPUT);
  pinMode(motorC2, OUTPUT);
  pinMode(motorD1, OUTPUT);
  pinMode(motorD2, OUTPUT);

////////////////////////////////////////////////////////////

}


void loop() {
  int pin34State = digitalRead(pin34);
  int pin35State = digitalRead(pin35);
  int pin33State = digitalRead(pin33);
  int pin25State = digitalRead(pin25);

  if (pin34State == HIGH && pin35State == HIGH && pin33State == HIGH && pin25State == HIGH) {
    moveForward();
  } else if (pin34State == LOW || pin35State == LOW) {
    left();
  } else if (pin33State == LOW || pin25State == LOW) {
    right();
  }
}

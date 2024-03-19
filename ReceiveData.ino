// 定义电机控制脚
#define motorA1 15 
#define motorA2 2
#define motorB1 4 
#define motorB2 16
#define motorC1 17 
#define motorC2 5
#define motorD1 18 
#define motorD2 19


#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;

const char* hotspotSSID = "yangyang";                        
const char* hotspotPassword = "yangyang666";                

const int localPort = 3545;



void setup(){
  // 配置电机控制脚为输出
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(motorC1, OUTPUT);
  pinMode(motorC2, OUTPUT);
  pinMode(motorD1, OUTPUT);
  pinMode(motorD2, OUTPUT);

  Serial.begin(115200);

  WiFi.softAP(hotspotSSID, hotspotPassword);
  IPAddress ipAddress = WiFi.softAPIP();
  Serial.print("Hotspot IP address: ");
  Serial.println(ipAddress);

  udp.begin(localPort);
  Serial.printf("Listening on UDP port %d\n", localPort);
}

// 控制电机前进
void moveForward() {
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
void moveBackward() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  digitalWrite(motorC1, LOW);
  digitalWrite(motorC2, HIGH);
  digitalWrite(motorD1, LOW);
  digitalWrite(motorD2, HIGH);
}

// 控制电机左转
void turnLeft() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  digitalWrite(motorC1, HIGH);
  digitalWrite(motorC2, LOW);
  digitalWrite(motorD1, LOW);
  digitalWrite(motorD2, HIGH);
}

// 控制电机右转
void turnRight() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  digitalWrite(motorC1, LOW);
  digitalWrite(motorC2, HIGH);
  digitalWrite(motorD1, HIGH);
  digitalWrite(motorD2, LOW);
}

// 控制电机顺时针旋转
void rotateClockwise() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  digitalWrite(motorC1, LOW);
  digitalWrite(motorC2, HIGH);
  digitalWrite(motorD1, LOW);
  digitalWrite(motorD2, HIGH);
}

// 控制电机逆时针旋转
void rotateCounterClockwise() {
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

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char packetData[255];
    int len = udp.read(packetData, 255);
    if (len > 0) {
      packetData[len] = 0;
      Serial.printf("Received: %s\n", packetData);
      
      // 解析接收到的数据
      float angleX, angleY, angleZ;
      sscanf(packetData, "%f,%f,%f", &angleX, &angleY, &angleZ);
      
      // 根据条件调用不同的函数
      if (angleX < -50) {
        moveForward();
      } else if (angleX > 50) {
        moveBackward();
      }
      
      if (angleY < -50) {
        //rotateCounterClockwise();
        turnLeft();
      } else if (angleY > 50) {
        //rotateClockwise();
        turnRight();
      }
      
      // if (angleZ < -30) {
      //   turnRight();
      // } else if (angleZ > 30) {
      //   turnLeft();
      // }
      if (abs(angleX) <= 50 && abs(angleY) <= 50){// && abs(angleZ) <= 30) {
        stop();                                                                              // 请将此函数修改为您停止小车动作的函数
      }
    }
  }
}

//通过WiFi模块接收摇杆信号的小车上的esp32

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

WiFiUDP Udp;

const char* hotspotSSID     = "yangyang";
const char* hotspotPassword = "yangyang666";
const int localPort = 3545; // 自身的端口号



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


void setup() {

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
  Serial.begin(115200);
  // WiFi.begin(ssid, password);

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.println("Connecting to WiFi...");
  // }

  WiFi.softAP(hotspotSSID, hotspotPassword);
  IPAddress ipAddress = WiFi.softAPIP();
  Serial.print("Hotspot IP address: ");
  Serial.println(ipAddress);


  Serial.println("Connected to WiFi");
  Udp.begin(localPort);
}

void loop() {
  int packetSize = Udp.parsePacket();
  // if (packetSize) {
  //   int x, y, button;
  //   Udp.read((char*)&x, sizeof(x));
  //   Udp.read((char*)&y, sizeof(y));
  //   Udp.read((char*)&button, sizeof(button));
  //   Serial.print(x); Serial.print(", ");
  //   Serial.print(y); Serial.print(", ");
  //   Serial.println(button);
  if (packetSize) {
    char packetData[255];
    int len = Udp.read(packetData, 255);
    if (len > 0) {
      packetData[len] = 0;
      Serial.printf("Received: %s\n", packetData);
      
      // 解析接收到的数据
      int x, y, button;
      sscanf(packetData, "%d,%d,%d", &x, &y, &button);
      if(x == 0 && y > 0 && y < 3000)
      {
          moveForward();
      }
      else if(x > 4000)
      {
          moveBackward();
      }
      else if(y > 4000 && x > 0)
      {
          turnLeft();
      }
      else if(x > 0 && y == 0)
      {
          turnRight();
      }
      else if(y > 4000 && x == 0)
      {
          rotateCounterClockwise();
      }
      else if(x == 0 && y == 0)
      {
          rotateClockwise();
      }
      else // 当没有其他情况满足时，调用stop()
      {
          stop();
      }
    }
  }
}


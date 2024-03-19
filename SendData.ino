//发送
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h>

MPU6050 mpu6050(Wire);
WiFiUDP udp;

const char* ssid = "yangyang";       // 替换为您的WiFi名称
const char* password = "yangyang666"; // 替换为您的WiFi密码

const char* receiverIP = "192.168.4.1"; // 替换为接收者的IP地址
const int receiverPort = 3545;               // 替换为接收者使用的端口号

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  udp.beginPacket(receiverIP, receiverPort);
}

void loop() {
  mpu6050.update();

  float angleX = mpu6050.getAngleX();
  float angleY = mpu6050.getAngleY();
  float angleZ = mpu6050.getAngleZ();

  // 构建发送数据
  //String sendData = angleX + "," + String(angleY) + "," + String(angleZ);
  String sendData = String(angleX) + "," + String(angleY) + "," + String(angleZ);

  // 发送数据
  udp.beginPacket(receiverIP, receiverPort);
  
  // 将字符串转换为字节数组并发送
  udp.write((const uint8_t*)sendData.c_str(), sendData.length());
  
  udp.endPacket();

  Serial.println("Data sent: " + sendData);

  delay(100); // 间隔一秒发送一次数据
}

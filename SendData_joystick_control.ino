//带摇杆的esp32程序

#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;

const char* remoteIp = "192.168.4.1"; // 另一个ESP32的IP地址
const int remotePort = 3545; // 另一个ESP32的端口号

const char* ssid     = "yangyang";
const char* password = "yangyang666";

const int VRx = 34;
const int VRy = 35;
const int SW = 33;

void setup() {
  Serial.begin(115200);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}



void loop() {
  int x = analogRead(VRx);
  int y = analogRead(VRy);
  int button = digitalRead(SW);
  
  char packetBuffer[255];
  sprintf(packetBuffer, "%d,%d,%d", x, y, button);

  Udp.beginPacket(remoteIp, remotePort);
  Udp.write((uint8_t*)packetBuffer, strlen(packetBuffer)); 
  Udp.endPacket();

  delay(100); // delay a bit
}


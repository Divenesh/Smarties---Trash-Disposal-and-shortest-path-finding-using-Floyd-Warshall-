#include <SoftwareSerial.h>
#define DEBUG true

// Ultrasonic sensor pins
int trigPin1 = 9;
int echoPin1 = 8;
int trigPin2 = 5;
int echoPin2 = 4;

// Wi-Fi credentials
const char* ssid = "A-05-13-TIME_2.4G";
const char* password = "rentdeer@A0513";
const char* server = "192.168.101.5"; // Flask server IP

// SoftwareSerial for ESP8266 (use voltage divider on TX to ESP RX)
SoftwareSerial espSerial(10, 11); // RX (to TX of ESP), TX (to RX of ESP)

float duration_us, distance_cm;

void setup() {
  Serial.begin(9600);         // For debugging
  espSerial.begin(115200);      // Use 9600 for SoftwareSerial

  // Sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Connect to Wi-Fi
  connectToWiFi();
}

void loop() {
  long range1 = ultrasonicSense1();
  long range2 = ultrasonicSense2();
  int gasValue = gas();

  // Prepare HTTP GET query parameters
  String data = "gas=" + String(gasValue) + "&ultrasonic1=" + String(range1) + "&ultrasonic2=" + String(range2);
  Serial.println("Sending data: " + data);

  // Send to Flask server
  sendData(data);

  delay(5000); // Send every 5 seconds
}

void connectToWiFi() {
  sendCommand("AT+RST\r\n", 2000);                 // Reset
  Serial.println("IM Resetting");
  delay(3000);
  sendCommand("AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"", 10000); // Extended delay for connection
  Serial.println("IM Connecting");
  delay(3000);
  sendCommand("AT+CWMODE=1\r\n", 1000);            // Set mode to STA
  delay(3000);
  sendCommand("AT+CIFSR\r\n", 2000);               // Check IP address
  Serial.println("IM Starting Server");
  delay(3000);
  Serial.println("Wi-Fi should now be connected.");
}

int ultrasonicSense1() {
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration_us = pulseIn(echoPin1, HIGH);
  distance_cm = 0.017 * duration_us;
  Serial.print("Ultrasonic1: ");
  Serial.println(distance_cm);
  return distance_cm;
}

int ultrasonicSense2() {
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration_us = pulseIn(echoPin2, HIGH);
  distance_cm = 0.017 * duration_us;
  Serial.print("Ultrasonic2: ");
  Serial.println(distance_cm);
  return distance_cm;
}

int gas() {
  int sensorValue = analogRead(A0);
  Serial.print("Gas: ");
  Serial.println(sensorValue);
  return sensorValue;
}

void sendData(String data) {
  sendCommand("AT+CIPCLOSE", 1000);  // Close any previous connection
  sendCommand("AT+CIPSTART=\"TCP\",\"" + String(server) + "\",5000", 5000); // Connect to server

  String httpRequest = "GET /data?" + data + " HTTP/1.1\r\nHost: " + String(server) + "\r\nConnection: close\r\n\r\n";
  int length = httpRequest.length();

  sendCommand("AT+CIPSEND=" + String(length), 2000);
  espSerial.print(httpRequest);
  Serial.print("HTTP Request Sent: ");
  Serial.println(httpRequest);

  // Wait and print response
  long timeout = millis() + 5000;
  while (millis() < timeout) {
    while (espSerial.available()) {
      char c = espSerial.read();
      Serial.write(c);
    }
  }
  Serial.println();
}

void sendCommand(String command, int maxTime) {
  espSerial.println(command);
  Serial.println(">> " + command);

  long int time = millis();
  while ((millis() - time) < maxTime) {
    while (espSerial.available()) {
      char c = espSerial.read();
      Serial.write(c);
    }
  }
  Serial.println();
}

#include <SoftwareSerial.h>

int trigPin1 = 9;    // TRIG pin
int echoPin1 = 8;    // ECHO pin
int trigPin2 = 5;    // TRIG pin
int echoPin2 = 4;    // ECHO pin

float duration_us, distance_cm;

// // Replace these with your Wi-Fi credentials
// const char* ssid = "none";
// const char* password = "12345678";
// const char* server = "192.168.243.217"; // Change this to your server's IP address

// SoftwareSerial espSerial(2, 3); // RX, TX for ESP8266

void setup() {
  Serial.begin(9600);
  // espSerial.begin(115200); // Initialize SoftwareSerial for ESP8266
  
  // Initialize pins for the ultrasonic sensors
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  // connectToWiFi();
}

void loop() {
  long range1 = ultrasonicSense1(); 
  long range2 = ultrasonicSense2();
  int gasValue = gas();

  String data = "gas=" + String(gasValue) + "&ultrasonic1=" + String(range1) + "&ultrasonic2=" + String(range2);
  Serial.println("Sending data: " + data); // Print data being sent for debugging
  // sendData(data);
  delay(5000);
}

// void connectToWiFi() {
//   sendCommand("AT+RST", 2000);
//   sendCommand("AT+CWMODE=1", 1000);
//   sendCommand("AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"", 10000); // Extended delay for connection

//   // Check if connected
//   sendCommand("AT+CIFSR", 1000); // This command should return the IP address if connected
//   Serial.println("Wi-Fi connection established.");
// }

int ultrasonicSense1() {
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration_us = pulseIn(echoPin1, HIGH);
  distance_cm = 0.017 * duration_us;
  Serial.print("Ultrasonic1 :");
  Serial.println(distance_cm);
  return distance_cm;
}

int ultrasonicSense2() {
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration_us = pulseIn(echoPin2, HIGH);
  distance_cm = 0.017 * duration_us;
  Serial.print("Ultrasonic2 :");
  Serial.println(distance_cm);
  return distance_cm;
}

int gas() {
  int sensorValue = analogRead(A0);
  return sensorValue;
}

// void sendData(String data) {
//   // Close any previous connection
//   sendCommand("AT+CIPCLOSE", 1000);

//   sendCommand("AT+CIPSTART=\"TCP\",\"" + String(server) + "\",5000", 5000);
//   sendCommand("AT+CIPSEND=" + String(data.length() + 44), 2000); // Adjusted length to include additional HTTP headers
  
//   String httpRequest = "GET /data?" + data + " HTTP/1.1\r\nHost: " + String(server) + "\r\nConnection: close\r\n\r\n";
//   // espSerial.print(httpRequest);
//   // Serial.print("HTTP Request: ");
//   // Serial.println(httpRequest); // Print the HTTP request for debugging

//   delay(5000); // Increased delay to ensure the request is fully sent

//   // Print the response from the server
//   while (espSerial.available()) {
//     Serial.write(espSerial.read());
//   }
// }

// void sendCommand(String command, int maxTime) {
//   // espSerial.println(command);
//   long int time = millis();
//   while ((time + maxTime) > millis()) {
//     while (espSerial.available()) {
//       char c = espSerial.read();
//       // Serial.print(c); // Print each character to the serial monitor
//     }
//   }
// }

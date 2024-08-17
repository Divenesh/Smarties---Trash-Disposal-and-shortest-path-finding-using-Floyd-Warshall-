#include <Servo.h> 
#define MoistPin A0
#define IRPin 4
Servo servo;


void setup() {
  servo.attach(9);
  Serial.begin(9600);
  pinMode(IRPin, INPUT); // Pin set as input

}

void loop() {

  int SensorValue = digitalRead(IRPin);
  Serial.println(SensorValue);
  if (digitalRead(IRPin)) // if Pin logic is HIGH
  {
    Serial.println("Object not detected"); // display on Serial monitor when object detected 
    
  }

  else {
   Serial.println("Object detected"); // display on Serial when object not detected 
   readSensor();
  }

  delay(5000);
}

// void loop() {
//   
//   Serial.print("SensorPin Value: ");
//   Serial.println(SensorValue);
//   // Serial.print("Analog output: ");
//   // Serial.println(IRSensorValue());   delay(3000);
// }

int readSensor() {
  int sensorValue = analogRead(MoistPin); 
  int outputValue = map(sensorValue, 0, 1023, 255, 0); 
  Serial.println(outputValue);
  if (outputValue > 5){
    servo.write(60);
    delay(2000);
    servo.write(90);
  } 
  else {
    servo.write(120);
    delay(2000);
    servo.write(90);
  }   

}

int IRSensorValue() {



}
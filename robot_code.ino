#include <Wire.h>
#include <SoftwareSerial.h>

// Define Constants
//#define trigPin2 13
//#define echoPin2 12
#define trigPin 11
#define echoPin 10

// Connections to A4988
const int dirPin = 2;  // Direction
const int stepPin = 3; // Step

// Motor steps per rotation
const int STEPS_PER_REV = 200;
int x = 0;

// Motor A
int enA = 9;
int in1 = 8;
int in2 = 7;
int MotorSpeed1 = 0;
// Motor B
int enB = 4;
int in3 = 6;
int in4 = 5;
int MotorSpeed2 = 0;
float duration, distance;
//float duration2, distance2;
int lock = 1;
SoftwareSerial softSerial(1, 0);


void setup() {
  Serial.begin(9600);
  softSerial.begin(9600);
  // Setup the pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
//  pinMode(trigPin2, OUTPUT);
//  pinMode(echoPin2, INPUT);
  //  Wire.begin(8);
  //  Wire.onReceive(receiveEvent); // register event

}
//void receiveEvent() {
//      distance = Wire.read();    // receive byte as an integer
//      Serial.println(distance);// print the integer
//      Serial.print("recived");
//      }

void loop() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, MotorSpeed1);

  // Set Motor B forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, MotorSpeed2);
  // Set motor direction clockwise
  
  digitalWrite(dirPin, HIGH);

  // Spin motor one step 
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(1000);


//  // Write a pulse to the HC-SR04 Trigger Pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
//
//  digitalWrite(trigPin2, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin2, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin2, LOW);
//  // Measure the response from the HC-SR04 Echo Pin
//
  //duration2 = pulseIn(echoPin2, HIGH);
  duration = pulseIn(echoPin, HIGH);
//  // Determine distance from duration
//  // Used 343 metres per second as speed of sound
  distance = (duration / 2) * 0.0343;
  //distance2 = (duration2 / 2) * 0.0343;

  // Send results to Serial Monitor
  
  Serial.print(x);
  //Serial.print(distance2);
  Serial.print("round: ");
  Serial.println(distance);
//  if ((distance2 <= 30) && (lock == 0)) {
//    MotorSpeed1 = 0;
//    MotorSpeed2 = 0;
//    lock = 1;
//  }
  // Set Motor A forward
  if (lock == 0) {
    lock = 1;
    if (distance <= 40 ) {     
      if (x > 170 || x < 10) {
        MotorSpeed1 = 250;
        MotorSpeed2 = 150;
      }
      else
      {
        MotorSpeed1 = 150;
        MotorSpeed2 = 250;
      }
    }
    else
    {
      MotorSpeed1 = 200;
      MotorSpeed2 = 200;
    }
  }

  lock = 0;
  if (x == 200)x = 0;
  else x++;
}

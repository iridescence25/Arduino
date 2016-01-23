/*
Servo Control
ARDUINO TRAINER - [AVERAGE LEVEL]

This sketch was compiled and tested using ARDUINO MEGA 2560.
This sketch is using Analog Smoothing Method in order to stabilize jitters while controlling the Servo.
This sketch is about controlling Servo Motor using a Potentiometer.
The potentiometer will act as INPUT and is connected to an Analog Pin (A0).
The Servo Motor will acr as OUTPUT and is connected to a PWM Pin (D2).

Date Created: November 23, 2015
Created by: Harvey Oroceo, BSCpE
*/

#include <Servo.h>          // Include Servo Library
Servo myServo;              // Servo Motor Object Instance
int servoControl = 0;       // Potentiometer 1

//ANALOG SMOOTHING METHOD DECLARATIONS
int servoReading[10];       // Analog Smoothing Reading (Array size: 10. This can be increased to further smoothen the servo, however, response time will take longer
int servoIndex = 0;         // Index of the current reading in the Array
int servoTotal = 0;         // Total Analog Readings
int servoAverage = 0;       // Average Analog Values

// The Setup() function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);       // Initialize Serial Communication (TX0/RX0) at 9600 bits per second
  myServo.attach(2);        // Attach Servo Instance to PWM Pin D2
}

// The Loop() function runs over and over again forever
void loop() {
  AnalogSmoothing(analogRead(0));   // Read Analog Values
  Convert(servoAverage);            // Convert Analog Values
  executeServo();                   // Execute Servo Movement
  Serial.println("Servo Value [0 - 180]: " + String(servoControl));    // Display Servo Values in Serial Monitor
  delay(1);                         // Wait for the Servo
}

// Method that Rationalizes Potentiometer Analog Values (0-1023) to Servo Analog Values (0-180)
void Convert(int potentiometer1){
  servoControl = map(potentiometer1, 0, 1023, 0, 180);
}

// Method that sends Analog Values to the Servo
void executeServo(){
  myServo.write(servoControl);
}

// Method for Smoothing Analog Values
void AnalogSmoothing(int potentiometer1){
  // Subtract the last reading
  servoTotal = servoTotal - servoReading[servoIndex];
  // Read from the Sensor
  servoReading[servoIndex] = potentiometer1;
  // Add the reading to the total
  servoTotal = servoTotal + servoReading[servoIndex];
  // Advance to the next position of the Array
  servoIndex = servoIndex + 1;

  // If we're at the end of the Array
  if(servoIndex >= 10){
    // ...wrap around to the beginning
    servoIndex = 0;
  }
  // Calculate the Average
  servoAverage = servoTotal / 10;
}

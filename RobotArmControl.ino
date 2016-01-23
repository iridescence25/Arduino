/*
ROBOTIC ARM CONTROL
A COMPONENT FROM IOT ARTDESK (FACTORY) - (ADVANCED LEVEL)

This sketch was compiled and tested using ARDUINO MEGA 2560.
This sketch is using Analog Smoothing Method in order to stabilize jitters while controlling the Robotic Arm.
This sketch is about controlling the Robotic Arm (E-GRA) using Four (4) Potentiometers.
The Four (4) Potentiometers will act as INPUTS and are connected to Analog Pins (A0-A3).
The Four (4) Robotic Arm Servos will act as OUTPUTS and are connected to PWM Pins (D2-D5).

Date Created: November 8, 2015
Created by: Harvey Oroceo, BSCpE
*/

#include <Servo.h>          // Include Servo Library  

// VARIABLE DECLARATIONS
// Servo instances
Servo claw;                 // First Servo that does the grip
Servo push;                 // Second Servo that does the pushing and pulling
Servo lift;                 // Third Servo that does the lifting up and down
Servo platform;             // Fourth Servo that does the platform rotation

// Variables that store Potentiometer Values
int clawControl = 0;        // Potentiometer 1
int pushControl = 0;        // Potentiometer 2
int liftControl = 0;        // Potentiometer 3
int platformControl = 0;    // Potentiometer 4

// ANALOG SMOOTHING METHOD DECLARATIONS
// Arrays that store Ten (10) Analog Readings
int clawReading[10];
int pushReading[10];
int liftReading[10];
int platformReading[10];

// Variables that act as the Indexes of the current reading in the Arrays
int clawIndex = 0;
int pushIndex = 0;
int liftIndex = 0;
int platformIndex = 0;

// Variables that store Total Analog Readings
int clawTotal = 0;
int pushTotal = 0;
int liftTotal = 0;
int platformTotal = 0;

// Variables that store Average Analog Values
int clawAverage = 0;
int pushAverage = 0;
int liftAverage = 0;
int platformAverage = 0;

// The Setup() function runs once when you press reset or power the board
void setup(){
  Serial.begin(9600);       // Initialize Serial Communication (TX0/RX0) at 9600 bits per second

  // Attach Servos to PWM Pins
  claw.attach(2);           // PWM Pin D2
  push.attach(3);           // PWM Pin D3
  lift.attach(4);           // PWM Pin D4
  platform.attach(5);       // PWM Pin D5
}

// The Loop() function runs over and over again forever
void loop(){
  AnalogSmoothing(analogRead(0), analogRead(1), analogRead(2), analogRead(3));      // Read Analog Values
  Convert(clawAverage, pushAverage, liftAverage, platformAverage);                  // Convert Analog Values
  RunRobot();                                                                       // Execute Servo Movement
  Serial.println("Claw: " + String(clawControl) + " Push: " + String(pushControl) + // Display Servo Values in Serial Monitor
    " Lift: " + String(liftControl) + " Platform: " + String(platformControl));
  delay(5);                                                                         // Wait for the Servo
}

// Method that Rationalizes Potentiometer Analog Values (0-1023) to Servo Analog Values (0-180)
void Convert(int potentiometer1, int potentiometer2, int potentiometer3, int potentiometer4) {
  clawControl = map(potentiometer1, 0, 1023, 0, 180);
  pushControl = map(potentiometer2, 0, 1023, 0, 180);
  liftControl = map(potentiometer3, 0, 1023, 0, 180);
  platformControl = map(potentiometer4, 0, 1023, 0, 180);
}

// Method that sends Analog Values to the Servos
void RunRobot() {
  claw.write(clawControl);
  push.write(pushControl);
  lift.write(liftControl);
  platform.write(platformControl);
}

// Method for Smoothing Analog Values
void AnalogSmoothing(int potentiometer1, int potentiometer2, int potentiometer3, int potentiometer4) {
  // Subtract the last reading
  clawTotal = clawTotal - clawReading[clawIndex];
  pushTotal = pushTotal - pushReading[pushIndex];
  liftTotal = liftTotal - liftReading[liftIndex];
  platformTotal = platformTotal - platformReading[platformIndex];

  // Read from the Sensor
  clawReading[clawIndex] = potentiometer1;
  pushReading[pushIndex] = potentiometer2;
  liftReading[liftIndex] = potentiometer3;
  platformReading[platformIndex] = potentiometer4;

  // Add the reading to the total
  clawTotal = clawTotal + clawReading[clawIndex];
  pushTotal = pushTotal + pushReading[pushIndex];
  liftTotal = liftTotal + liftReading[liftIndex];
  platformTotal = platformTotal + platformReading[platformIndex];

  // Advance to the next position of the Array
  clawIndex = clawIndex + 1;
  pushIndex = pushIndex + 1;
  liftIndex = liftIndex + 1;
  platformIndex = platformIndex + 1;

  // If we're at the end of the Array
  if (clawIndex >= 10) {
    // ...wrap around to the beginning
    clawIndex = 0;
  }
  if (pushIndex >= 10) {
    pushIndex = 0;
  }
  if (liftIndex >= 10) {
    liftIndex = 0;
  }
  if (platformIndex >= 10) {
    platformIndex = 0;
  }

  // Calculate the Average
  clawAverage = clawTotal / 10;
  pushAverage = pushTotal / 10;
  liftAverage = liftAverage / 10;
  platformAverage = platformAverage / 10;
}

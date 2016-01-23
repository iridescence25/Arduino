/*
Obstacle Avoidance
A COMPONENT FROM IOT ARTDESK (MOBILE ROBOTICS) - [ADVANCED LEVEL]

This sketch was compiled and tested using GIZDUINO ATMEGA168
This sketch is made to make the Primerobot to avoid obstacles and prevent itself from going outside the line.
The Primerobot utilizes its (2) Proximity Sensors, an Ultrasonic Sensor, a Motor Driver Shield, and a Line Follower Module.

The following connections are (When the Switch of the Primerobot is facing you):

Proximity Sensor:
The Left Promity "OUT" is connected to (D2).
The Right Proximity "OUT" is connected to (D3).
 
The Motor Driver Shield:
OUTA Forward/Reverse is connected to (D8).
OUTA Speed Input is connected to (D9).
OUTB Speed Input is connected to (D10).
OUTB Forward/Reverse is connected to (D11).

Ultrasonic Sensor:
Trigger Pin is connected to (D12).
Echo Pin is connected to (D4).

Date Created: November 24, 2015
Created by: Harvey Oroceo, BSCpE
*/

#include <NewPing.h>                   // Include library for Ultrasonic Sensor

#define trigger 12                     // Define trigger to be assigned to D12
#define echo 4                         // Define echo to be assigned to D4
#define maxDistance 100                // Define maxDistance to 100 cm (Note: The hardware maximum limit is 350 cm)

// Create a new instance of NewPing
NewPing sonar(trigger, echo, maxDistance);

// Variable that stores speed value
int speedA = 0;
int speedB = 0;

// Distance Threshold for SONAR
int sonarThreshold = 0;

// The Setup() function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);                 // Initialize Serial Communication (TX0/RX0) at 9600 bits per second
  
  // Set (D8-D11) as OUTPUT for the MOTOR SHIELD
  pinMode(8, OUTPUT);                 // Forwards/Reverses DC Motor or Bipolar Stepper Motor at OUTA
  pinMode(9, OUTPUT);                 // Adjusts speed of DC Motor or Bipolar Stepper Motor at OUTA
  pinMode(10, OUTPUT);                // Adjusts speed of DC Motor or Bipolar Stepper Motor at OUTB
  pinMode(11, OUTPUT);                // Forwards/Reverses DC Motor or Bipolar Stepper Motor at OUTB

  // Set (D2-D3) as INPUT for the Proximity Sensor
  pinMode(2, INPUT);                  // Left Proximity Sensor
  pinMode(3, INPUT);                  // Right Proximity Sensor
}

// The Loop() function runs over and over again forever
void loop() {
  // Set Motor Speed
  speedA = 150;                        // Speed 150 (Note: Maximum speed is 255                        
  speedB = 150;                        // Speed 150 (Note: Maximum speed is 255
  analogWrite(9, speedA);              // Set OUTA speed
  analogWrite(10, speedB);             // Set OUTB speed
  
  // Check front obstacles first
  if(sonarDetect() == false){
    // .. then check boundaries
    if(lineDetect(digitalRead(7), digitalRead(5)) == false){
    // .. then finally check the sides
    proximityDetect(digitalRead(2), digitalRead(3));
    }
  }
  delay(10);
}

// Function for the Proximity Sensor
void proximityDetect(int left, int right){
  if(left == 0 && right == 1){
    digitalWrite(11, LOW);
    Serial.println("Obstacle detected on the left. Turning right.");
  }

  else if(left == 1 && right == 0){
    digitalWrite(8, LOW);
    Serial.println("Obstacle detected on the right. Turning left.");
  }

  else if(left == 0 && right == 0){
    digitalWrite(8, HIGH);
    digitalWrite(11, LOW);
    delay(500);
    Serial.println("Obstacle detected at two sides. Turning around.");
  }

  else{
    digitalWrite(8, HIGH);
    digitalWrite(11, HIGH);
    Serial.println("Moving forward. No obstacles detected.");
  }
}

// Function for the Ultrasonic Sensor
bool sonarDetect(){
  int currentPing = sonar.ping();
  sonarThreshold = currentPing / US_ROUNDTRIP_CM;
  if(sonarThreshold <= 20){
    digitalWrite(8, HIGH);
    digitalWrite(11, LOW);
    delay(500);
    Serial.println("Obstacle detected at the front. Turning around.");
    return true;
  }
  return false;
}

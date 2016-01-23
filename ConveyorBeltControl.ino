/*
CONVEYOR BELT CONTROL
A COMPONENT FROM IOT ARTDESK (FACTORY) - (AVERAGE LEVEL)

This sketch was compiled and tested using ARDUINO MEGA 2560 and MOTOR DRIVER SHIELD (LB11847)
This sketch is about controlling the Conveyor Belt Prototyping Set using Four (4) Switches and Two (2) Potentiometers
The Four (4) Switches will act as INPUTS and are connected to (D22, D24, D26, D28)
The Two (2) Potentiometers will act as INPUTS and are connected to Analog Pins (A8-A9)
Digital Pins (D8-D11) will act as OUTPUTS for the MOTOR DRIVER SHIELD
DO NOT USE PINS (D2-D7) AND (A0-A5) FOR IT IS BEING USED BY THE MOTOR DRIVER SHIELD

Date Created: November 8, 2015
Created by: Harvey Oroceo, BSCpE
*/

// Variable that stores speed value
int speedA = 0;
int speedB = 0;

// Variable for telling us the current state of the Motor
String motorStateA = "FORWARD";        
String motorStateB = "FORWARD";                         

// The Setup() function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);                 // Initialize Serial Communication (TX0/RX0) at 9600 bits per second
  // Set (D8-D11) as OUTPUT for the MOTOR SHIELD
  pinMode(8, OUTPUT);                 // Forwards/Reverses DC Motor or Bipolar Stepper Motor at OUTA
  pinMode(9, OUTPUT);                 // Adjusts speed of DC Motor or Bipolar Stepper Motor at OUTA
  pinMode(10, OUTPUT);                // Adjusts speed of DC Motor or Bipolar Stepper Motor at OUTB
  pinMode(11, OUTPUT);                // Forwards/Reverses DC Motor or Bipolar Stepper Motor at OUTB

  // Set (D22, D24, D26, D28) as INPUT for the Switches
  pinMode(22, INPUT);                 // Forward OUTA
  pinMode(24, INPUT);                 // Reverse OUTA
  pinMode(26, INPUT);                 // Forward OUTB
  pinMode(28, INPUT);                 // Reverse OUTB
}

// The Loop() function runs over and over again forever
void loop() {
  // Set Motor Speed
  speedA = map(analogRead(8), 0, 1023, 0, 255);         //Rationalize Analog Values (0-1080) to Motor Speed Values (0-255)
  speedB = map(analogRead(9), 0, 1023, 0, 255);         //Rationalize Analog Values (0-1080) to Motor Speed Values (0-255)
  analogWrite(9, speedA);                               // Set OUTA speed
  analogWrite(10, speedB);                              // Set OUTB speed
  
  // If D22 is pressed, OUTA will move forward
  if (digitalRead(22) == HIGH && digitalRead(24) == LOW){   
    digitalWrite(8, LOW);                               // Forward OUTA
    motorStateA = "FORWARD";
  }
  // If D24 is pressed, OUTA will move backwards
  else if (digitalRead(22) == LOW && digitalRead(24) == HIGH){
    digitalWrite(8, HIGH);                              // Reverse OUTA
    motorStateA = "REVERSE";
  }

  // If D26 is pressed, OUTB will move forward
  if (digitalRead(26) == HIGH && digitalRead(28) == LOW){    
    digitalWrite(11, LOW);                              // Forward OUTB
    motorStateB = "FORWARD";
  }
  // If D28 is pressed, OUTB will move backwards
  else if (digitalRead(26) == LOW && digitalRead(28) == HIGH){
    digitalWrite(11, HIGH);                             // Reverse OUTB
    motorStateB = "REVERSE";
  }
  // Display Motor Status
  Serial.println("Motor A: " + motorStateA + " Speed: " + speedA + " Motor B: " + motorStateB + " Speed: " + speedB);
}

/*
Color Maze Avoidance
A COMPONENT FROM IOT ARTDESK (MOBILE ROBOTICS) - [ADVANCED LEVEL]

This sketch was compiled and tested using GIZDUINO ATMEGA168
This sketch is made to make the Primerobot to avoid red colors on the floor and get out of the maze.
The Primerobot utilizes its TCS3200 Color Recognition Sensor and the Motor Driver Shield. 

The following connections are (When the Switch of the Primerobot is facing you):

The Motor Driver Shield:
OUTA Forward/Reverse is connected to (D8).
OUTA Speed Input is connected to (D9).
OUTB Speed Input is connected to (D10).
OUTB Forward/Reverse is connected to (D11).

TCS3200 Color Recognition Sensor:
VCC is connected to 5v
GND is connected to GND
s0 is connected to (D5)
s1 is connected to (D6)
s2 is connected to (D7)
s3 is connected to (D8)
OUT is connected to (D14)
OE is connected to GND


Date Created: December 16, 2015
Created by: Harvey Oroceo, BSCpE
*/

// Variables  
int red = 0;  
int green = 0;  
int blue = 0; 

// TCS3200 Color Recognition Sensor Pins
const int s0 = 5;                     // Output frequency scaling selection input
const int s1 = 6;                     // Output frequency scaling selection input
const int s2 = 7;                     // Photodiode type selection inputs
const int s3 = 16;                    // Photodiode type selection inputs
const int out = 14;                   // Output frequency


// The Setup() function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);                 // Initialize Serial Communication (TX0/RX0) at 9600 bits per second
  
  // Set (D8-D11) as OUTPUT for the MOTOR SHIELD
  pinMode(8, OUTPUT);                 // Forwards/Reverses DC Motor or Bipolar Stepper Motor at OUTA
  pinMode(9, OUTPUT);                 // Adjusts speed of DC Motor or Bipolar Stepper Motor at OUTA
  pinMode(10, OUTPUT);                // Adjusts speed of DC Motor or Bipolar Stepper Motor at OUTB
  pinMode(11, OUTPUT);                // Forwards/Reverses DC Motor or Bipolar Stepper Motor at OUTB

  // Set TCS230 Color Recognition Sensor Pin Setup
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  // Set s0 and s1 to HIGH
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
}

// The Loop() function runs over and over again forever
void loop() {
  // Set Motor Speed
  speedA = 150;                        // Speed 150 (Note: Maximum speed is 255                        
  speedB = 150;                        // Speed 150 (Note: Maximum speed is 255
  analogWrite(9, speedA);              // Set OUTA speed
  analogWrite(10, speedB);             // Set OUTB speed
  
}

void color(){    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}

/*
PROXIMITY BUZZER ALARM
ARDUINO TRAINER - [BEGINNER LEVEL]

This sketch was compiled and tested using ARDUINO MEGA 2560.
This sketch is about sensing objects within the Proximity Sensor's range then the Buzzer will ring.
The (+5V) and (GND) of the Proximity Sensor are connected to the Arduino's (+5V) and (GND), respectively.
The (GND) of the Buzzer is also connected to the Arduino's (GND). (Please use the breadboard for parallel connections)
The (OUT) of the Proximity Sensor is connected to (D2).
The (+5V) of the Buzzer is connected to (D3).

Note: The proximity sensor is using INVERSE LOGIC. (Default state is always HIGH)

Date Created: November 23, 2015
Created by: Harvey Oroceo, BSCpE
*/

int buzzer = 3;   // Assign the buzzer to Digital Pin 3
int sensor = 2;   // Assign the proximity sensor to Pin 2

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(buzzer, OUTPUT);    // Set the buzzer as OUTPUT
  pinMode(sensor, INPUT);     // Set the proximity sensor as INPUT
}

// the loop function runs over and over again forever
void loop() {
  if(digitalRead(sensor) == LOW){   // If the sensor senses something, trigger the buzzer
    digitalWrite(buzzer, HIGH);
    delay(150);                     // Set delay to prevent buzzer's jittery sounds
  }
  if(digitalRead(sensor) == HIGH){  // If the sensor senses nothing, turn of the buzzer
    digitalWrite(buzzer, LOW);
  }
}

/*
LED SEQUENCE
ARDUINO TRAINER - [BEGINNER LEVEL]

This sketch was compiled and tested using ARDUINO MEGA 2560.
This sketch is about coding LED Sequences.
Four (4) Green LEDs and Four (4) Red LEDs will act as OUTPUTS and are assigned to (D5 - D12)

Date Created: November 23, 2015
Created by: Harvey Oroceo, BSCpE
*/

int leds[]={5, 6, 7, 8, 9, 10, 11, 12};     // Place the pin numbers in a array


// The setup function runs once when you press reset or power the board
void setup() {
  for (int pin = 0; pin < 8; pin++){        // Assign each pin number in the array as an OUTPUT
    pinMode(leds[pin], OUTPUT);
  }
}

// The loop function runs over and over again forever
void loop() {
  sequenceOne();
  sequenceTwo();
  sequenceThree();
  defaultState();
}

// These are the Functions for different Sequences
void sequenceOne(){                         // LED Sequence "Running Lights at 1 sec delay"
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  delay(500);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  delay(500);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  delay(500);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(500);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delay(500);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(500);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(12, LOW);
}

void sequenceTwo(){                         // LED Sequence "Lights Up at 1 sec delay"
  digitalWrite(5, HIGH);
  digitalWrite(9, HIGH);
  delay(500);

  digitalWrite(6, HIGH);
  digitalWrite(10, HIGH);
  delay(500);

  digitalWrite(7, HIGH);
  digitalWrite(11, HIGH);
  delay(500);

  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);
  delay(500);

  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  delay(500);

  digitalWrite(7, LOW);
  digitalWrite(11, LOW);
  delay(500);

  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  delay(500);

  digitalWrite(5, LOW);
  digitalWrite(9, LOW);
   delay(500);
}

void sequenceThree(){                          // LED Sequence "Alternating Lights at 1 sec delay" 
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
  digitalWrite(12, LOW);
  delay(500);
  
  digitalWrite(6, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  digitalWrite(9, LOW);
  digitalWrite(11, LOW);
  delay(500);

  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
  digitalWrite(12, LOW);
  delay(500);
  
  digitalWrite(6, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  digitalWrite(9, LOW);
  digitalWrite(11, LOW);
  delay(500);
}

void defaultState(){
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  delay(1);
}

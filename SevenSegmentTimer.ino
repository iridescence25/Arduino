/*
Seven Segment Timer
ARDUINO TRAINER - [AVERAGE LEVEL]

This sketch was compiled and tested using ARDUINO MEGA 2560.
This sketch is about coding a Coundown Timer using the Seven Segments.
The (D5-D2) are connected to (BCD A0-A3) of the first Seven Segment, respectively. These pins will act as OUTPUTS.
The (D9-D6) are connected to (BCD A0-A3) of the second Seven Segment, respectively. These pins will act as OUTPUTS.
The (+5V) and (OUT) of the Seven Segment are connected to the (+5V) and (OUT) of the Arduino, respectively.

Date Created: November 24, 2015
Created ny: Harvey Oroceo, BSCpE
*/

int controls[] = {2, 3, 4, 5, 6, 7, 8, 9};              // Place the pin numbers in a array

// The setup function runs once when you press reset or power the board
void setup() {
  for(int pin = 0; pin < 8; pin++){                     // Assign each pin number in the array as an OUTPUT
    pinMode(controls[pin], OUTPUT);
  }
}

// The loop function runs over and over again forever
void loop() {
  for(int seg1Time = 9; seg1Time >= 0; seg1Time--){     // Tens Place Countdown Loop (Segment 1)
    segmentOne(seg1Time);                               // Call Function for Tens Place Seven Segment (Segment 1)                               
    for(int seg2Time = 9; seg2Time >= 0; seg2Time--){   // Ones Place Countdown Loop (Segment 2)
      segmentTwo(seg2Time);                             // Call Function for Ones Place Seven Segment (Segment 2)
      delay(1000);                                      // 1 Second Delay
    }
  }
}

void segmentOne(int displayTime){                       // Segment 1 Function
  switch(displayTime){
    case 1:              
    digitalWrite(2, LOW);                               // Values follows Binary Format: Bin 0 0 0 1 = Dec 1 
    digitalWrite(3, LOW);                               // ("0" = LOW and "1" = HIGH)
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    break;

    case 2:
    digitalWrite(2, LOW);                               // Values follows Binary Format: Bin 0 0 1 0 = Dec 2
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    break;

    case 3:
    digitalWrite(2, LOW);                               // Values follows Binary Format: Bin 0 0 1 1 = Dec 3 and so on...
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    break;

    case 4:
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    break;

    case 5:
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    break;

    case 6:
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    break;

    case 7:
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    break;

    case 8:
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    break;

    case 9:
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    break;

    default:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    break;
  }
}

void segmentTwo(int displayTime){                       // Segment 2 Function   
  switch(displayTime){
    case 1:
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    break;

    case 2:
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    break;

    case 3:
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    break;

    case 4:
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    break;

    case 5:
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    break;

    case 6:
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    break;

    case 7:
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    break;

    case 8:
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    break;

    case 9:
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    break;
    
    default:
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    break;
  }
}

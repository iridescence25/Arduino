/*
LCD Passcode Access
ARDUINO TRAINER - [AVERAGE LEVEL]

This sketch was compiled and tested using ARDUINO MEGA 2560.
This sketch is about entering Passcode using Pushbuttons then displays information at the LCD (2x16).
This sketch also shows how to compare arrays, how to debounce pushbutton combinations properly and how to show scrolling text without limit.
The following connections, with respect to the Arduino Trainer are:

LCD Pin => Arduino Trainer Potentiometer
V0 => Potentiometer Base (Mid Pin) -- Adjust Screen Contrast by turning the potentiometer's knob

LCD Pins => Arduino MEGA 2560 Pins

GND => GND
VCC => 5V
RS  => D12
RW  => GND
E   => D11
D0  => No Connection
D1  => No Connection
D2  => No Connection
D3  => No Connection
D4  => D5
D5  => D4
D6  => D3
D7  => D2

Push Button Pins => Arduino MEGA 2560 Pins

PB1 => D22
PB2 => D24
PB3 => D26
PB4 => D28
PB5 => D30
PB6 => D32

IR Sensor => Arduino MEGA 2560 Pin
Signal => D34

Buzzer => Arduino MEGA 2560 Pin
Vcc => D36

Date Created: December 5, 2015
Created by: Harvey Oroceo, BSCpE
*/

#include <LiquidCrystal.h>                                        // Include the library for LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);                            // Initialize the library with the numbers of the interface pins

  int input[] = { 22, 24, 26, 28, 30, 32, 34 };                   // Declare an array containing all INPUTS

  int screenWidth = 16;                                           // '16' x 2 LCD
  int screenHeight = 2;                                           // 16 x '2' LCD

  bool accessStatus;                                              // Access Status variable
  bool reset;                                                     // Reset variable

  int passCode[6];                                                // Array container for passcodes to be entered
  int unlock[] = { 3, 6, 1, 5, 2, 1 };                            // Array container for passcodes to be compared

// The Setup() function runs once when you press reset or power the board
void setup() {
  lcd.begin(screenWidth, screenHeight);                           // Set up the LCD's number of columns and rows

  pinMode(36, OUTPUT);                                            // Set pin as OUTPUT for Buzzer
  
  for(int pin = 0; pin <= 7; pin++){                              // Set each pin in the array as INPUT
    pinMode(input[pin], INPUT);
  }
}

// The Loop() function runs over and over again forever
void loop() {
  // Welcome Message
  welcomeScreen("WELCOME! (^_^)", "This is the IOT ARTDESK - Arduino Trainer. Please swipe IR Sensor to begin!!!");
  reset = false;                                                  // Set reset variable to false
  
  while(reset == false){                                          // Don't do void loop() function until authentication() function returns a value 
    accessStatus = authentication();                              // Call authentication() function
    
    if(accessStatus == true){                                     // If returned value is TRUE...
      lcd.setCursor(0,0);                                         // Set cursor to the upper left side
      lcd.print("ACCESS GRANTED!");                               // Tell the user that the code entered is correct
      
      digitalWrite(36, HIGH);                                     // 1 sec buzzer
      delay(1000);
      digitalWrite(36, LOW);
      
      for(int countDown = 10; countDown > 0; countDown--){        // Do a countdown before returning to Welcome Screen
        lcd.setCursor(0,0);                                       // Set cursor to the upper left side                         
        lcd.print("ACCESS GRANTED!");                             // Tell the user that the code entered is correct (Note: This is included again because of lcd.clear() function)                             
        lcd.setCursor(0,1);                                       // Set cursor to the lower left side 
        lcd.print("Returning... " + String(countDown));           // Show Countdown
        delay(1000);                                              // 1 sec delay
        lcd.clear();                                              // Clear the screen before printing something again
      }
      reset = true;                                               // Exit while loop
    }
    
    else{                                                         // If returned value is FALSE...
      lcd.setCursor(0,0);                                         // Set cursor to the upper left side
      lcd.print("ACCESS DENIED!");                                // Tell the user that the code entered is correct
      
      digitalWrite(36, HIGH);                                     // 200 millisecond buzzer
      delay(200);
      digitalWrite(36, LOW);
      delay(200);
      digitalWrite(36, HIGH);                                     // 200 millisecond buzzer
      delay(200);
      digitalWrite(36, LOW);
      
      for(int countDown = 10; countDown > 0; countDown--){        // Do a countdown before returning to Welcome Screen
        lcd.setCursor(0,0);                                       // Set cursor to the upper left side 
        lcd.print("ACCESS DENIED!");                              // Tell the user that the code entered is not correct (Note: This is included again because of lcd.clear() function)   
        lcd.setCursor(0,1);                                       // Set cursor to the lower left side 
        lcd.print("Returning... " + String(countDown));           // Show Countdown
        delay(1000);                                              // 1 sec delay
        lcd.clear();                                              // Clear the screen before printing something again
      }
      reset = true;                                               // Exit while loop
    }
  }
}

// This function will display the Static Banner and Scrolling Welcome Screen
void welcomeScreen(String line1, String line2){
  int stringStart = 0, stringStop = 0;                            // Variables for Scrolling Logic
  int scrollCursor = screenWidth;
  
  while(digitalRead(34) == HIGH){                                 // While the sensor detects nothing, continue...
    lcd.setCursor(0, 0);                                          // Set the cursor at the upper left side
    lcd.print(line1);                                             // Print the Banner
    lcd.setCursor(scrollCursor, 1);                               // Set the cursor at the upper right side
    lcd.print(line2.substring(stringStart, stringStop));          // Print the scrolling text. Note: Substring is used to tell the LCD the exact strings to be displayed
    delay(200);                                                   // 200 millisecond delay per scroll
    lcd.clear();                                                  // Clear the LCD Screen and position the cursor at the upper left side

    // Left Side Text Scrolling Logic (Note: Scrolling Text is available in LiquidCrystal Library. However, it doesn't allow you to enter long texts.)
    if(stringStart == 0 && scrollCursor > 0){
      scrollCursor--;
      stringStop++;
    } 
    else if (stringStart == stringStop){
      stringStart = stringStop = 0;
      scrollCursor = screenWidth;
    }
    else if (stringStop == line2.length() && scrollCursor == 0) {
      stringStart++;
    } 
    else {
    stringStart++;
    stringStop++;
    }
  }
}

//This function will determine the authentication of a user
bool authentication(){
  bool access = false;                                            // Set access variable to false

  lcd.setCursor(0, 0);                                            // Set the cursor at the upper left side
  lcd.print("Passcode Input:");                                   // Tell the user to enter passcode
  lcd.setCursor(0, 1);                                            // Set the cursor at the lower left side

  int storeValue = 0;                                             // Set storeValue to 0
   
  while (access == false){                                        // While access is false, do the methods in it continuously
    // Push Button 1
    if(digitalRead(22) == HIGH){                                  // If Push Button 1 is pressed... (Note all Push Buttons have the same logic...)
      lcd.print("*");                                             // Show asterisk sign, telling the user that he/she entered a code successfully
      passCode[storeValue] = 1;                                   // Store "1" in the array with respect to storeValue. storeValue tells which positioning should the value "1" be stored
      storeValue++;                                               // Increment positioning in the array
      digitalWrite(36, HIGH);                                     // 100 millisecond Buzzer per click
      delay(100);                                                 // Use this delay not only for buzzer, but also for debouncing the push button
      digitalWrite(36, LOW);
      while(digitalRead(22) == HIGH){                             // Do nothing if the push button is still pressed. This is to prevent the arduino from reading same button as another input repeatedly.
        // Do nothing. Wait for the button to be unpressed.
      }
    }

    // Push Button 2
    if(digitalRead(24) == HIGH){
      lcd.print("*");
      passCode[storeValue] = 2;
      storeValue++;
      digitalWrite(36, HIGH);
      delay(100);
      digitalWrite(36, LOW);
      while(digitalRead(24) == HIGH){
        // Do nothing. Wait for the button to be unpressed.
      }
    }

    // Push Button 3
    if(digitalRead(26) == HIGH){
      lcd.print("*");
      passCode[storeValue] = 3;
      storeValue++;
      digitalWrite(36, HIGH);
      delay(100);
      digitalWrite(36, LOW);
      while(digitalRead(26) == HIGH){
        // Do nothing. Wait for the button to be unpressed.
      }
    }

    // Push Button 4
    if(digitalRead(28) == HIGH){
      lcd.print("*");
      passCode[storeValue] = 4;
      storeValue++;
      digitalWrite(36, HIGH);
      delay(100);
      digitalWrite(36, LOW);
      while(digitalRead(28) == HIGH){
        // Do nothing. Wait for the button to be unpressed.
      }
    }

    // Push Button 5
    if(digitalRead(30) == HIGH){
      lcd.print("*");
      passCode[storeValue] = 5;
      storeValue++;
      digitalWrite(36, HIGH);
      delay(100);
      digitalWrite(36, LOW);
      while(digitalRead(30) == HIGH){
        // Do nothing. Wait for the button to be unpressed.
      }
    }

    // Push Button 6
    if(digitalRead(32) == HIGH){
      lcd.print("*");
      passCode[storeValue] = 6;
      storeValue++;
      digitalWrite(36, HIGH);
      delay(100);
      digitalWrite(36, LOW);
      while(digitalRead(32) == HIGH){
        // Do nothing. Wait for the button to be unpressed.
      }
    }

    // Comparing Arrays
    if(storeValue == 6){                                          // if storeValue reaches 6... (This means that array for storing passcodes is now full)
      for(int index = 0; index <= 5; index++){                    // Initiate a for loop that will loop to all elements in both arrays
        int storedCode = passCode[index];                         // Store the value recovered from an array
        int compareCode = unlock[index];                          // Store the value recovered from an array
        
        if(storedCode != compareCode){                            // If a stored code in passCode[] array didn't matched with the compare code in the unlock[] array...
          return false;                                           // ... break the loop and return false.
        }
      }
      access = true;                                              // If all elements in both arrays matched, end the while loop.
    }
  }
  lcd.clear();                                                    // Clear the screen before printing something again
  return true;                                                    // Return true
}

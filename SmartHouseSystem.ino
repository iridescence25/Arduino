/*
SMART HOUSE SYSTEM
SMART HOUSE SIMULATOR - [INTERMEDIATE LEVEL]

This sketch was compiled and tested using ARDUINO MEGA 2560.
This sketch is intended to work with Raspberry Pi 2 Model B running the FaceDetection Program.
This sketch will utilize 4 Push Buttons, 1 Mini PIR Motion Sensor, 1 LCD Display, 1 Keypad, 1 Fingerprint Sensor and 8 Bright LEDS.
The following connections, with respect to the Arduino Trainer are (Refer to Arduino MEGA 2560 Pin Configurations):

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

PB1 => D6
PB2 => D7
PB3 => D8
PB4 => D9


Mini PIR Motion Sensor => Arduino MEGA 2560 Pins

  + Pin => 5V
  - Pin => GND
OUT Pin => D10


Raspberry Pi => Arduino MEGA 2560 Pins

GND    => GND
Pin 3  => D20
Pin 5  => D21


Adafruit Optical Fingerprint Sensor  Arduino MEGA 2560 Pins
GND => GND
5V  => 5V
Green Wire (IN) => RX3 (D15)
White Wire (OUT) => TX3 (D14)


4x4 Keypad => Arduino MEGA 2560 Pins

Pin 1 => D28
Pin 2 => D26
Pin 3 => D24
Pin 4 => D22
Pin 5 => D30
Pin 6 => D32
Pin 7 => D34
Pin 8 => D36


Bright LEDs => Arduino MEGA 2560 Pins

All GND => GND
L1 => D38
l2 => D40
L3 => D42
L4 => D44
L5 => D46
L6 => D48
L7 => D50
L8 => D52


Servos => Arduino MEGA 2560 Pins
All GND => GND
All 5V => 5V
Door Servo Signal => 13
Garage Servo Signal => 45

Date Created: December 23, 2015
Created by: Harvey Oroceo, BSCpE
*/

#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal.h>                                                  
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <Servo.h>


// Servo instances
Servo door;
Servo garage;


// LCD Configuration
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);                                      // Initialize the library with the numbers of the interface pins
int screenWidth = 16;                                                       // '16' x 2 LCD
int screenHeight = 2;                                                       // 16 x '2' LCD


// Push Button Configuration
int startFaceRecognition = 6;
int l1Button = 7;
int l2Button = 8;
int l3Button = 9;


// Mini PIR Motion Sensor Configuration
int motionSensor = 10;


// Raspberry Pi Pin Configuration
int sendSignal = 20;
int receiveSignal = 21;


// Adafruit Optical Fingerprint Sensor Configuration
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial3);


// 4x4 Keypad Configuration
const byte ROWS = 4;                                                        // four rows
const byte COLS = 4;                                                        // three columns
char keys[ROWS][COLS] = {                                                   // Custom Mapping
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {28, 26, 24, 22};                                      // connect to the row pinouts of the keypad
byte colPins[COLS] = {36, 34, 32, 30,};                                     // connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );   // Keymap instance


// Bright LED's Pin Configuration
int brightLED[] = { 
  38, 40, 42, 44, 46, 48, 50, 52
};


// LCD Logic Variables
String line1 = "WELCOME!!!";
String line2 = "Press PB1 to run Face Recognition! or Press Any Key on the Keypad for Garage Pass";
int stringStart = 0, stringStop = 0;                            
int scrollCursor = screenWidth;
unsigned long scrollDelay = 200;
unsigned long scrollPrevTime = 0;


// Second Authentication Variable
bool checkFingerPrint = true;
int displayOnce = 0;


// Motion Sensor Variables
unsigned long lightDelay = 3000;
unsigned long lightPrevTime = 0;


// Garage Variables
bool disableRaspberryPi = false;
bool disableScrollText = false;
bool disableKeyEvent = false;
bool enableGarage = false;
char passCode[6];                                             
char unlock[] = { '3', '6', '1', '7', 'A', 'D' };
int storeValue = 0;                      


// Lights Variables
int l1State = LOW;
int l2State = LOW;


// The Setup() function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // Set up the LCD's number of columns and rows
  lcd.begin(screenWidth, screenHeight); 
                                      
  // Set Push Buttons as INPUT
  pinMode(startFaceRecognition, INPUT);
  pinMode(l1Button, INPUT);
  pinMode(l2Button, INPUT);
  pinMode(l3Button, INPUT);
  
  // Set Mini PIR Motion Sensor OUT as INPUT
  pinMode(motionSensor, INPUT);

  // Set connections to Raspberry Pi
  pinMode(sendSignal, OUTPUT);
  pinMode(receiveSignal, INPUT);

  // Start Adaruit Optical Fingerprint Sensor
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }

  // Set all Bright LED's as OUTPUT
  for(int pin = 0; pin < 8; pin++){
    pinMode(brightLED[pin], OUTPUT);
  }

  // Add event listener for this keypad
  keypad.addEventListener(keypadEvent);

  // Attach Servos to PWM Pins
  door.attach(13);
  garage.attach(45);
}

void loop() {
  unsigned long currentTime = millis();
  messageDisplay(currentTime);
  motionDetect(currentTime);
  garagePass();
  raspberryPi();
  houseLights();
}

// Function for Displaying Text
void messageDisplay(unsigned long getTime){
  if(disableScrollText == false){
    lcd.setCursor(0, 0);                                          // Set the cursor at the upper left side
    lcd.print(line1);                                             // Print the Banner
    lcd.setCursor(scrollCursor, 1);                               // Set the cursor at the upper right side
    lcd.print(line2.substring(stringStart, stringStop));          // Print the scrolling text. Note: Substring is used to tell the LCD the exact strings to be displayed
    if(getTime - scrollPrevTime >= scrollDelay){
      scrollPrevTime = getTime;
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
}

// Function for sending and receiving signals to and from Raspberry Pi
void raspberryPi(){
  if(disableRaspberryPi == false){
    if(digitalRead(startFaceRecognition) == HIGH){
      digitalWrite(sendSignal, HIGH);
      line1 = "Face Recog.";
      line2 = "Please look at the camera until the light goes out.";
    }
    if(digitalRead(receiveSignal) == HIGH){
      openDoor();
    }
    if(digitalRead(receiveSignal) == LOW){
     closeDoor();
    }
  }
}

// Function for Opening Door and Light
void openDoor(){
  if(displayOnce == 0){
    line1 = "Fingerprint Scan";
    line2 = "Place your thumb at the Fingerprint Sensor.";
  }
  
  if(checkFingerPrint == fingerPrintScan()){
    line1 = "Access Granted!";
    line2 = "Face and Fingerprint Recognized! You may now enter!";
    displayOnce = 1;
    door.write(180);
    digitalWrite(38, HIGH);
  }
}

// Function for Closing Door and Light
void closeDoor(){
  door.write(90);
  digitalWrite(38, LOW);
  if(displayOnce == 1){
    line1 = "WELCOME!!!";
    line2 = "Press PB1 to run Face Recognition! or Press Any Key on the Keypad for Garage Pass";
    displayOnce == 0;
  }
}

// Second Authentication
bool fingerPrintScan(){
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return false;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return false;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return false;
    default:
      Serial.println("Unknown error");
      return false;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return false;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return false;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return false;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return false;
    default:
      Serial.println("Unknown error");
      return false;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return false;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return false;
  } else {
    Serial.println("Unknown error");
    return false;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return true;
}

// Function for Motion Sensor
void motionDetect(unsigned long getTime){
  if(digitalRead(motionSensor) == HIGH){
    digitalWrite(46, HIGH);
    digitalWrite(48, HIGH);
    digitalWrite(50, HIGH);
    digitalWrite(52, HIGH);
    lightPrevTime = getTime;
  }
  if(getTime - lightPrevTime >= lightDelay){
    lightPrevTime = getTime;
    digitalWrite(46, LOW);
    digitalWrite(48, LOW);
    digitalWrite(50, LOW);
    digitalWrite(52, LOW);
  }
}

// Function for Opening Garage using Keypad
void garagePass(){
  if(enableGarage == true){
    char key = keypad.getKey();
    
    lcd.setCursor(0, 0);
    lcd.print("Enter Pass:");
    lcd.setCursor(storeValue, 1);

    if(key){                                  
      lcd.print("*");                                             
      passCode[storeValue] = key;                                  
      storeValue++;                                               
    }

    if(storeValue == 6){                                          
      for(int index = 0; index <= 5; index++){                    
        int storedCode = passCode[index];                         
        int compareCode = unlock[index];                          
        
        if(storedCode != compareCode){
          lcd.setCursor(0, 0);                          
          lcd.print("Access Denied!");
          disableRaspberryPi = false;
          disableScrollText = false;
          disableKeyEvent = false;
          enableGarage = false;
          delay(3000);
          line1 = "WELCOME!!!";
          line2 = "Press PB1 to run Face Recognition! or Press Any Key on the Keypad for Garage Pass";
        }
      }
      lcd.print("Access Granted!");
      storeValue = 0;
      disableRaspberryPi = false;
      disableScrollText = false;
      disableKeyEvent = false;
      enableGarage = false;
      garage.write(180);
      delay(5000);
      garage.write(0);
      line1 = "WELCOME!!!";
      line2 = "Press PB1 to run Face Recognition! or Press Any Key on the Keypad for Garage Pass";
    }
  }
}

void keypadEvent(KeypadEvent key){
  if(disableKeyEvent == false){
  switch (keypad.getState()){
    case PRESSED:
      disableRaspberryPi = true;
      disableScrollText = true;
      disableKeyEvent = true;
      enableGarage = true;
      break;
    }
  }
}

// Function for House Lights
void houseLights(){
  if(digitalRead(l1Button) == HIGH){
    if(l1State == LOW){
      l1State = HIGH;
    }
    if(l1State == HIGH){
      l1State = LOW;
    }
    digitalWrite(40, l1State);
    while(l1Button){
      // Do nothing. Wait for the button to be unpressed.
    }
  }
  if(digitalRead(l2Button) == HIGH){
    if(l2State == LOW){
      l2State = HIGH;
    }
    if(l2State == HIGH){
      l2State = LOW;
    }
    digitalWrite(42, l2State);
    while(l2Button){
      // Do nothing. Wait for the button to be unpressed.
    }
  }
}

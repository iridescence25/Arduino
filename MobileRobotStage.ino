/*
MOBILE ROBOT STAGE CONTROL
IOT ARTDESK (MOBILE ROBOT STAGE) - (ADVANCED LEVEL)

This sketch was compiled and tested using ARDUINO MEGA 2560 and WS2811 LED PIXEL STRING
This sketch is sbout controlling light algorithms in the stage by using the Adafruit_Neopixel.h library
(D6) is connected to the (DI) INPUT side of WS2811 (Green Wire)
(+5v) is connected to the (Vcc) INPUT side of WS2811  (White Wire)
(GND) is connected to the (GND) INPUT side of WS2811  (Red Wire)

Date Created: Decemeber 13, 2015
Created by: Harvey Oroceo, BSCpE
 */

// Adafruit Library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 7

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, PIN, NEO_RGB + NEO_KHZ800);

// IMPORTANT: To reduce WS2811 burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// NOTE: The WS2811 is arranged from left to right and right to left vice versa.
// Therefore, we created arrays so the sequence is always left to right. 
const int A[20] = {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19 };
const int B[20] = {  39,  38,  37,  36,  35,  34,  33,  32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20 };
const int C[20] = {  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59 };
const int D[20] = {  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66,  65,  64,  63,  62,  61,  60 };
const int E[20] = {  80, 81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,   99 };
const int F[20] = { 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100 };
const int G[20] = { 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139 };
const int H[20] = { 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140 };
const int I[20] = { 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179 };
const int J[20] = { 199, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180 };

// Color Values
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t off = strip.Color(0, 0, 0);

// Movement Incrementation
int boxMovement = 1;
int tankMovement = 1;
int bombMovement = 1;

// Front Panel Push Buttons
int welcome = 2;
int reset = 3;
int stage_1 = 4;
int stage_2 = 5;
int stage_3 = 6;

// The Setup() function runs once when you press reset or power the board
void setup() {
  for(int pin = 2; pin < 7; pin++){
    pinMode(pin, INPUT);
  }
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

// The Loop() function runs over and over again forever
void loop() {
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127, 0, 0), 50); // Red
  theaterChase(strip.Color(0, 0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
}

// Stage 1 is a maze-like pattern
void stage1(){
  //Line A
  bool completed = false;
  while(completed == false){
    for(uint16_t i=0; i < 20; i++){
      strip.setPixelColor(A[i], red);
   }
  
   //Line B
    strip.setPixelColor(B[0], red);
    strip.setPixelColor(B[12], red);
    strip.setPixelColor(B[19], red);
  
   //Line C
    strip.setPixelColor(C[0], red);
    strip.setPixelColor(C[12], red);
    strip.setPixelColor(C[19], red);
  
    //Line D
    strip.setPixelColor(D[0], red);
    strip.setPixelColor(D[3], red);
    strip.setPixelColor(D[4], red);
    strip.setPixelColor(D[5], red);
    strip.setPixelColor(D[6], red);
    strip.setPixelColor(D[7], red);
    strip.setPixelColor(D[8], red);
    strip.setPixelColor(D[9], red);
    strip.setPixelColor(D[15], red);
    strip.setPixelColor(D[16], red);
    strip.setPixelColor(D[19], red);

    //Line E
    strip.setPixelColor(E[0], red);
    strip.setPixelColor(E[9], red);
    strip.setPixelColor(E[15], red);
    strip.setPixelColor(E[19], red);
  
    //Line F
    strip.setPixelColor(F[0], red);
    strip.setPixelColor(F[9], red);
    strip.setPixelColor(F[10], red);
    strip.setPixelColor(F[11], red);
    strip.setPixelColor(F[12], red);
    strip.setPixelColor(F[13], red);
    strip.setPixelColor(F[14], red);
    strip.setPixelColor(F[15], red);
    strip.setPixelColor(F[19], red);
  
    //Line G
    strip.setPixelColor(G[0], red);
    strip.setPixelColor(G[1], red);
    strip.setPixelColor(G[2], red);
    strip.setPixelColor(G[3], red);
    strip.setPixelColor(G[4], red);
    strip.setPixelColor(G[5], red);
    strip.setPixelColor(G[6], red);
    strip.setPixelColor(G[9], red);
    strip.setPixelColor(G[10], green);
    strip.setPixelColor(G[11], green);
    strip.setPixelColor(G[12], red);
    strip.setPixelColor(G[13], red);
    strip.setPixelColor(G[14], red);
    strip.setPixelColor(G[15], red);
    strip.setPixelColor(G[18], red);
    strip.setPixelColor(G[19], red);
  
    //Line H
    strip.setPixelColor(H[0], red);
    strip.setPixelColor(H[1], green);
    strip.setPixelColor(H[9], red);
    strip.setPixelColor(H[18], red);
    strip.setPixelColor(H[19], red);
  
    //Line I
    strip.setPixelColor(I[0], red);
    strip.setPixelColor(I[1], green);
    strip.setPixelColor(I[9], red);
    strip.setPixelColor(I[18], red);
    strip.setPixelColor(I[19], red);
  
    //Line J
    for(uint16_t i=0; i < 20; i++){
      strip.setPixelColor(J[i], red);
    }
    strip.show();

    if(digitalRead(welcome) == HIGH){
      completed = true;
    }

    if(digitalRead(reset) == HIGH){
      stage1();
    }
   }
}

// Stage 2 is composed of moving obstacles
void stage2(){
  bool completed = false;
  unsigned long boxTime = 0;
  unsigned long tankTime = 0;
  unsigned long bombTime = 0;
  
  const long boxInterval = 100;
  const long tankInterval = 50;
  const long bombInterval = 150;
  
  while(completed == false){
    unsigned long currentTime = millis();
    if(currentTime - boxTime >= boxInterval){
      boxTime = currentTime;
      boxObstacle(boxMovement);
      boxMovement++;
    }

    if(currentTime - tankTime >= tankInterval){
      tankTime = currentTime;
      tankObstacle(tankMovement);
      tankMovement++;
      }

    if(currentTime - bombTime >= bombInterval){
      bombTime = currentTime;
      bombObstacle(bombMovement);
      bombMovement++; 
    }
    strip.show();

    if(digitalRead(welcome) == HIGH){
      completed = true;
    }

    if(digitalRead(reset) == HIGH){
      stage2();
    }
  }
}

// Stage 3 is for sumo-bot arena
void stage3() {
  uint16_t i, j;
  bool delayTime = true;
  unsigned long prevTime = 0;
  unsigned long wait = 20;
  bool completed = false;
  
  while(completed == false){
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }

       // Turn off the Inbounds
       for(int pos = 4; pos < 16; pos++){
         strip.setPixelColor(C[pos], off);
       }
       for(int pos = 4; pos < 16; pos++){
         strip.setPixelColor(D[pos], off);
       }
       for(int pos = 4; pos < 16; pos++){
         strip.setPixelColor(E[pos], off);
       }
       for(int pos = 4; pos < 16; pos++){
         strip.setPixelColor(F[pos], off);
       }
       for(int pos = 4; pos < 16; pos++){
          strip.setPixelColor(G[pos], off);
       }
       for(int pos = 4; pos < 16; pos++){
          strip.setPixelColor(H[pos], off);
       }
    
        strip.show();
        while(delayTime){
          unsigned long currentTime = millis();
          if(digitalRead(welcome) == HIGH){
            completed = true;
            delayTime = false;
          }

          if(digitalRead(reset) == HIGH){
            stage3();
          }
          
          if(currentTime - prevTime >= wait){
          prevTime = currentTime;
          delayTime = false;
          }
        }
    }
  }
}

// Box Obstacle Algorithm
void boxObstacle(int pos){
  switch(pos){
    case 1:
      strip.setPixelColor(J[5], red);
      strip.setPixelColor(J[6], red);

      strip.setPixelColor(A[5], off);
      strip.setPixelColor(A[6], off);


      //
      strip.setPixelColor(E[5], red);
      strip.setPixelColor(E[6], red);
      strip.setPixelColor(F[5], red);
      strip.setPixelColor(F[6], red);

      strip.setPixelColor(G[5], off);
      strip.setPixelColor(G[6], off);
      break;
 
    case 2:
      strip.setPixelColor(I[5], red);
      strip.setPixelColor(I[6], red);
      strip.setPixelColor(J[5], red);
      strip.setPixelColor(J[6], red);

      //
      strip.setPixelColor(D[5], red);
      strip.setPixelColor(D[6], red);
      strip.setPixelColor(E[5], red);
      strip.setPixelColor(E[6], red);

      strip.setPixelColor(F[5], off);
      strip.setPixelColor(F[6], off);
      break;

    case 3:
      strip.setPixelColor(H[5], red);
      strip.setPixelColor(H[6], red);
      strip.setPixelColor(I[5], red);
      strip.setPixelColor(I[6], red);

      strip.setPixelColor(J[5], off);
      strip.setPixelColor(J[6], off);

      //
      strip.setPixelColor(C[5], red);
      strip.setPixelColor(C[6], red);
      strip.setPixelColor(D[5], red);
      strip.setPixelColor(D[6], red);

      strip.setPixelColor(E[5], off);
      strip.setPixelColor(E[6], off);
      break;

    case 4:
      strip.setPixelColor(G[5], red);
      strip.setPixelColor(G[6], red);
      strip.setPixelColor(H[5], red);
      strip.setPixelColor(H[6], red);

      strip.setPixelColor(I[5], off);
      strip.setPixelColor(I[6], off);

      //
      strip.setPixelColor(B[5], red);
      strip.setPixelColor(B[6], red);
      strip.setPixelColor(C[5], red);
      strip.setPixelColor(C[6], red);

      strip.setPixelColor(D[5], off);
      strip.setPixelColor(D[6], off);
      break;

    case 5:
      strip.setPixelColor(F[5], red);
      strip.setPixelColor(F[6], red);
      strip.setPixelColor(G[5], red);
      strip.setPixelColor(G[6], red);

      strip.setPixelColor(H[5], off);
      strip.setPixelColor(H[6], off);

      //
      strip.setPixelColor(A[5], red);
      strip.setPixelColor(A[6], red);
      strip.setPixelColor(B[5], red);
      strip.setPixelColor(B[6], red);

      strip.setPixelColor(C[5], off);
      strip.setPixelColor(C[6], off);
      break;

    case 6:
      strip.setPixelColor(E[5], red);
      strip.setPixelColor(E[6], red);
      strip.setPixelColor(F[5], red);
      strip.setPixelColor(F[6], red);

      strip.setPixelColor(G[5], off);
      strip.setPixelColor(G[6], off);

      //
      strip.setPixelColor(A[5], red);
      strip.setPixelColor(A[6], red);

      strip.setPixelColor(B[5], off);
      strip.setPixelColor(B[6], off);
      boxMovement = 0;

      break;

    case 7:
      strip.setPixelColor(D[5], red);
      strip.setPixelColor(D[6], red);
      strip.setPixelColor(E[5], red);
      strip.setPixelColor(E[6], red);

      strip.setPixelColor(F[5], off);
      strip.setPixelColor(F[6], off);

      //
      strip.setPixelColor(J[5], red);
      strip.setPixelColor(J[6], red);

      strip.setPixelColor(A[5], off);
      strip.setPixelColor(A[6], off);
      break;

    case 8:
      strip.setPixelColor(C[5], red);
      strip.setPixelColor(C[6], red);
      strip.setPixelColor(D[5], red);
      strip.setPixelColor(D[6], red);

      strip.setPixelColor(E[5], off);
      strip.setPixelColor(E[6], off);

      //
      strip.setPixelColor(I[5], red);
      strip.setPixelColor(I[6], red);
      strip.setPixelColor(J[5], red);
      strip.setPixelColor(J[6], red);
      break;

    case 9:
      strip.setPixelColor(B[5], red);
      strip.setPixelColor(B[6], red);
      strip.setPixelColor(C[5], red);
      strip.setPixelColor(C[6], red);

      strip.setPixelColor(D[5], off);
      strip.setPixelColor(D[6], off);

      //
      strip.setPixelColor(H[5], red);
      strip.setPixelColor(H[6], red);
      strip.setPixelColor(I[5], red);
      strip.setPixelColor(I[6], red);

      strip.setPixelColor(J[5], off);
      strip.setPixelColor(J[6], off);
      break;

    case 10:
      strip.setPixelColor(A[5], red);
      strip.setPixelColor(A[6], red);
      strip.setPixelColor(B[5], red);
      strip.setPixelColor(B[6], red);

      strip.setPixelColor(C[5], off);
      strip.setPixelColor(C[6], off);  

      //
      strip.setPixelColor(G[5], red);
      strip.setPixelColor(G[6], red);
      strip.setPixelColor(H[5], red);
      strip.setPixelColor(H[6], red);

      strip.setPixelColor(I[5], off);
      strip.setPixelColor(I[6], off);
      break;

   case 11:
      strip.setPixelColor(A[5], red);
      strip.setPixelColor(A[6], red);

      strip.setPixelColor(B[5], off);
      strip.setPixelColor(B[6], off);
      boxMovement = 0;


      //
      strip.setPixelColor(F[5], red);
      strip.setPixelColor(F[6], red);
      strip.setPixelColor(G[5], red);
      strip.setPixelColor(G[6], red);

      strip.setPixelColor(H[5], off);
      strip.setPixelColor(H[6], off);
   }
}

// Tank Obstacle Algorithm
void tankObstacle(int pos){
  switch(pos){
    case 1:
      strip.setPixelColor(D[9], green);
      strip.setPixelColor(E[8], green);
      strip.setPixelColor(E[10], green);
      strip.setPixelColor(F[8], green);
      strip.setPixelColor(F[10], green);

      strip.setPixelColor(G[8], off);
      strip.setPixelColor(G[10], off);
  
    case 2:
      strip.setPixelColor(C[9], green);
      strip.setPixelColor(D[8], green);
      strip.setPixelColor(D[10], green);
      strip.setPixelColor(E[8], green);
      strip.setPixelColor(E[10], green);

      strip.setPixelColor(F[8], off);
      strip.setPixelColor(F[10], off);

    case 3:
      strip.setPixelColor(B[9], green);
      strip.setPixelColor(C[8], green);
      strip.setPixelColor(C[10], green);
      strip.setPixelColor(D[8], green);
      strip.setPixelColor(D[10], green);
      
      strip.setPixelColor(E[8], off);
      strip.setPixelColor(E[10], off);

    case 4:
      strip.setPixelColor(A[9], green);
      strip.setPixelColor(B[8], green);
      strip.setPixelColor(B[10], green);
      strip.setPixelColor(C[8], green);
      strip.setPixelColor(C[10], green);

      strip.setPixelColor(D[8], off);
      strip.setPixelColor(D[10], off);

    case 5:
      strip.setPixelColor(J[9], green);
      strip.setPixelColor(A[8], green);
      strip.setPixelColor(A[10], green);
      strip.setPixelColor(B[8], green);
      strip.setPixelColor(B[10], green);

      strip.setPixelColor(C[8], off);
      strip.setPixelColor(C[10], off);
      
    case 6:
      strip.setPixelColor(I[9], green);
      strip.setPixelColor(J[8], green);
      strip.setPixelColor(J[10], green);
      strip.setPixelColor(A[8], green);
      strip.setPixelColor(A[10], green);

      strip.setPixelColor(B[8], off);
      strip.setPixelColor(B[10], off);

    case 7:
      strip.setPixelColor(H[9], green);
      strip.setPixelColor(I[8], green);
      strip.setPixelColor(I[10], green);
      strip.setPixelColor(J[8], green);
      strip.setPixelColor(J[10], green);

      strip.setPixelColor(A[8], off);
      strip.setPixelColor(A[10], off);

    case 8:
      strip.setPixelColor(G[9], green);
      strip.setPixelColor(H[8], green);
      strip.setPixelColor(H[10], green);
      strip.setPixelColor(I[8], green);
      strip.setPixelColor(I[10], green);

      strip.setPixelColor(J[8], off);
      strip.setPixelColor(J[10], off);

    case 9:
      strip.setPixelColor(F[9], green);
      strip.setPixelColor(G[8], green);
      strip.setPixelColor(G[10], green);
      strip.setPixelColor(H[8], green);
      strip.setPixelColor(H[10], green);

      strip.setPixelColor(I[8], off);
      strip.setPixelColor(I[10], off);

    case 10:
      strip.setPixelColor(E[9], green);
      strip.setPixelColor(F[8], green);
      strip.setPixelColor(F[10], green);
      strip.setPixelColor(G[8], green);
      strip.setPixelColor(G[10], green);

      strip.setPixelColor(H[8], off);
      strip.setPixelColor(H[10], off);
      tankMovement = 1;
  }
}

// Bomb Obstacle Algorithm
void bombObstacle(int pos){
  switch(pos){
    case 1:
      strip.setPixelColor(E[15], blue);
      strip.setPixelColor(D[14], blue);
      strip.setPixelColor(D[16], blue);
      strip.setPixelColor(F[14], blue);
      strip.setPixelColor(F[16], blue);

    case 2:
      strip.setPixelColor(C[13], blue);
      strip.setPixelColor(C[17], blue);
      strip.setPixelColor(G[13], blue);
      strip.setPixelColor(G[17], blue);

    case 3:
      strip.setPixelColor(B[12], blue);
      strip.setPixelColor(B[18], blue);
      strip.setPixelColor(H[12], blue);
      strip.setPixelColor(H[18], blue);

    case 4:
      strip.setPixelColor(E[15], blue);
      strip.setPixelColor(D[14], off);
      strip.setPixelColor(D[16], off);
      strip.setPixelColor(F[14], off);
      strip.setPixelColor(F[16], off);
      strip.setPixelColor(C[13], off);
      strip.setPixelColor(C[17], off);
      strip.setPixelColor(G[13], off);
      strip.setPixelColor(G[17], off);
      strip.setPixelColor(B[12], off);
      strip.setPixelColor(B[18], off);
      strip.setPixelColor(H[12], off);
      strip.setPixelColor(H[18], off);
      bombMovement = 1;
  }
}


// Adafruit Default Strandtest Example...
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, unsigned long wait) {
  bool delayTime = true;
  unsigned long prevTime = 0;
    
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    
    strip.setPixelColor(i, c);
    strip.show();
    
    // Delay
    while(delayTime){
      unsigned long currentTime = millis();
      if(digitalRead(stage_1) == HIGH){
            stage1();
      }
      if(digitalRead(stage_2) == HIGH){
            stage2();
      }
      if(digitalRead(stage_3) == HIGH){
            stage3();
      }
      if(currentTime - prevTime >= wait){
       prevTime = currentTime;
       delayTime = false;
      }
    }
  }
}

void rainbow(unsigned long wait) {
  uint16_t i, j;
  bool delayTime = true;
  unsigned long prevTime = 0;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    
    while(delayTime){
      unsigned long currentTime = millis();
      if(digitalRead(stage_1) == HIGH){
            stage1();
      }
      if(digitalRead(stage_2) == HIGH){
            stage2();
      }
      if(digitalRead(stage_3) == HIGH){
            stage3();
      }
      if(currentTime - prevTime >= wait){
       prevTime = currentTime;
       delayTime = false;
      }
    }
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(unsigned long wait) {
  uint16_t i, j;
  bool delayTime = true;
  unsigned long prevTime = 0;
  
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    
    while(delayTime){
      unsigned long currentTime = millis();
      if(digitalRead(stage_1) == HIGH){
            stage1();
      }
      if(digitalRead(stage_2) == HIGH){
            stage2();
      }
      if(digitalRead(stage_3) == HIGH){
            stage3();
      }
      if(currentTime - prevTime >= wait){
       prevTime = currentTime;
       delayTime = false;
      }
    }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, unsigned long wait) {
  bool delayTime = true;
  unsigned long prevTime = 0;
  
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      while(delayTime){
        unsigned long currentTime = millis();
        if(digitalRead(stage_1) == HIGH){
            stage1();
        }
        if(digitalRead(stage_2) == HIGH){
            stage2();
        }
        if(digitalRead(stage_3) == HIGH){
            stage3();
        }
        if(currentTime - prevTime >= wait){
        prevTime = currentTime;
        delayTime = false;
        }
      }

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(unsigned long wait) {
  bool delayTime = true;
  unsigned long prevTime = 0;
  
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      while(delayTime){
        unsigned long currentTime = millis();
        if(digitalRead(stage_1) == HIGH){
            stage1();
        }
        if(digitalRead(stage_2) == HIGH){
            stage2();
        }
        if(digitalRead(stage_3) == HIGH){
            stage3();
        }
        if(currentTime - prevTime >= wait){
        prevTime = currentTime;
        delayTime = false;
        }
      }

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

/*
    e-Gizmo OLED Shield
 
 Sample codes
 
 Codes by:
 e-Gizmo Mechatronix Central
 http://www.e-gizmo.com

 ChangeLog:
 06/02/14 - @egizmoMehatronix Central 
          - SD library Modified and additional codes
            for gizDuino + and X.
      
           
 For gizDuino 328:(UnComment the two define ports
            if you are using the gizDuino 168/328 ONLY)
            
 For gizDuino + or X: Same procedure in + and X 
            if you want to use them. 
            
Go to the *selection of gizDuino Boards to use.
*/           

#include <SD.h>

const byte REG_SOFTRES = 0x01; //Software Reset
const byte REG_DDISP_ON_OFF = 0x02; //Display ON/OFF SET
const byte REG_DSTBY_ON_OFF = 0x03; //Stanby Mode Set
const byte REG_DFRAME = 0x04; //Set Frame Frequence
const byte REG_WriteDirection = 0x05; //Sets GRAM Writing Direction
const byte REG_ScanDirection = 0x06; //Row Scan Direction
const byte REG_DispSize = 0x07; //Display Size Set
const byte REG_IF_Bus_Sel = 0x08; //Interface bus Select
const byte REG_Data_Masking = 0x09; //Masking Data
const byte REG_MBOXSize = 0x0A; //Data Reading/Writing Box
const byte REG_DISPStart = 0x0B; //Display Start Address
const byte REG_DataWrite = 0x0C; //Reading/Write Dot matrix Display Data
const byte REG_READREG = 0x0D; //Read Register Status
const byte REG_DotCurrent = 0x0E; //Set Dot Marix Current Level
const byte REG_DotPeakCurrent = 0x0F; //Set Dot Marix Peak Current Level
const byte REG_PreC_Width = 0x1C; //Sets Precharge pulse width
const byte REG_PeakWidth = 0x1D; //Set Peak Pulse Width
const byte REG_PeakDelay = 0x1E; //Sets Peak Pulse Delay(0u~63u)
const byte REG_Row_Scan = 0x1F; //Set Row Scan Operation
const byte REG_IF_SEL = 0x2D; //Set Interface Mode
const byte REG_RGB_IF_CTRL = 0x2E; //RGB I/F Control
const byte REG_RGB_IF_POL = 0x2F; //Set RGB I/F Polarity
const byte REG_VCC_R_SEL = 0x30; //Set Internal Regulator for Row Scan
const byte REG_XTALK_Mode = 0x31; //Set XTALK Condition Setting
const byte REG_XTALK_EN = 0x32; //Set XTALK Enable
const byte REG_AGING_EN = 0x35; //Set AGING Mode
const byte REG_Gamma_Tune = 0x3A; //Set Gamma Correction Table Set
const byte REG_Gamma_Initial = 0x3B; //Set Gamma Correction Table Initialize

const byte A0B = 5;
const byte CSB = 4;
const byte WRB = 3;
const byte RES = 2;

byte RED;
byte GREEN;
byte BLUE;

unsigned int Y, X;

/*--------- Selection of gizDuino Boards to use ------------*/

/* For gizDuino 328 */
//#define PORTOLED PORTC
//#define PORTOLEDDDR DDRC

/* For gizDuino +   */
//#define PORTOLED PORTA
//#define PORTOLEDDDR DDRA

/* For gizDuino X  */
#define PORTOLED PORTF
#define PORTOLEDDDR DDRF

/*---------------------------------------------------------*/

const int chipSelect = 4;

void setup() {
  Serial.begin(9600);
    PORTOLEDDDR = ~0x00;    //D0-D7 output
    pinMode(A0B, OUTPUT);
    pinMode(CSB, OUTPUT);
    pinMode(WRB, OUTPUT);
    pinMode(RES, OUTPUT);

    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
//    WRITE_COMMAND(0x01); // Display ON/OFF SET
//    while(1);
    init_OLED();
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(SS, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(10, 11, 12, 13)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop() {
  while(1) {
  delay(3000);
        WRITE_COMMAND(REG_DISPStart);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_COMMAND(REG_DataWrite);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("1.bmp");
  
  // if the file is available, write to it:
  if (dataFile) {
    for(Y=0; Y<54; Y++) {
      dataFile.read();
    }      
    while (dataFile.available()) {
        WRITE_DATA(dataFile.read() >> 2);
    }
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  } 
  delay(3000);
  
        WRITE_COMMAND(REG_DISPStart);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_COMMAND(REG_DataWrite);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  dataFile = SD.open("adrian.bmp");

  // if the file is available, write to it:
  if (dataFile) {
    for(Y=0; Y<54; Y++) {
      dataFile.read();
    }      
    while (dataFile.available()) {
        WRITE_DATA(dataFile.read() >> 2);
    }
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  } 

  delay(3000);
  
        WRITE_COMMAND(REG_DISPStart);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_COMMAND(REG_DataWrite);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  dataFile = SD.open("dheyjem.bmp");

  // if the file is available, write to it:
  if (dataFile) {
    for(Y=0; Y<54; Y++) {
      dataFile.read();
    }      
    while (dataFile.available()) {
        WRITE_DATA(dataFile.read() >> 2);
    }
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  }

        WRITE_COMMAND(REG_DISPStart);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_COMMAND(REG_DataWrite);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  dataFile = SD.open("earvin.bmp");

  // if the file is available, write to it:
  if (dataFile) {
    for(Y=0; Y<54; Y++) {
      dataFile.read();
    }      
    while (dataFile.available()) {
        WRITE_DATA(dataFile.read() >> 2);
    }
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  } 

  
        WRITE_COMMAND(REG_DISPStart);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_COMMAND(REG_DataWrite);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  dataFile = SD.open("harvey.bmp");

  // if the file is available, write to it:
  if (dataFile) {
    for(Y=0; Y<54; Y++) {
      dataFile.read();
    }      
    while (dataFile.available()) {
        WRITE_DATA(dataFile.read() >> 2);
    }
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  } 

  
        WRITE_COMMAND(REG_DISPStart);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_COMMAND(REG_DataWrite);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  dataFile = SD.open("JB.bmp");

  // if the file is available, write to it:
  if (dataFile) {
    for(Y=0; Y<54; Y++) {
      dataFile.read();
    }      
    while (dataFile.available()) {
        WRITE_DATA(dataFile.read() >> 2);
    }
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  } 

  
        WRITE_COMMAND(REG_DISPStart);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_COMMAND(REG_DataWrite);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  dataFile = SD.open("jerash.bmp");

  // if the file is available, write to it:
  if (dataFile) {
    for(Y=0; Y<54; Y++) {
      dataFile.read();
    }      
    while (dataFile.available()) {
        WRITE_DATA(dataFile.read() >> 2);
    }
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  } 

  
        WRITE_COMMAND(REG_DISPStart);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_DATA(0x00);
        WRITE_COMMAND(REG_DataWrite);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  dataFile = SD.open("ren.bmp");

  // if the file is available, write to it:
  if (dataFile) {
    for(Y=0; Y<54; Y++) {
      dataFile.read();
    }      
    while (dataFile.available()) {
        WRITE_DATA(dataFile.read() >> 2);
    }
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  } 

  }    
    if(!digitalRead(7)) {
        if(RED > 0)
            RED--;
    }      
    if(!digitalRead(8)) {
        if(RED < 255)
            RED++;
    }      
    if(!digitalRead(9)) {
        if(GREEN > 0)
            GREEN--;
    }      
    if(!digitalRead(10)) {
        if(GREEN < 255)
            GREEN++;
    }      
    if(!digitalRead(11)) {
        if(BLUE > 0)
            BLUE--;
    }      
    if(!digitalRead(12)) {
        if(BLUE < 255)
            BLUE++;
    }      
    WRITE_COMMAND(REG_DotCurrent);
    WRITE_DATA(RED >> 4);
    WRITE_DATA(RED & 0x0F);
    WRITE_DATA(GREEN >> 4);
    WRITE_DATA(GREEN & 0x0F);
    WRITE_DATA(BLUE >> 4);
    WRITE_DATA(BLUE & 0x0F);
    Serial.print(RED);
    Serial.print(GREEN);
    Serial.println(BLUE);
    delay(100);
}

void init_OLED() {
    WRITE_COMMAND(REG_SOFTRES); // Software Reset
    
//    WRITE_COMMAND(REG_DDISP_ON_OFF); // Display ON/OFF SET
//    WRITE_DATA(0x00); // Display OFF
    
    WRITE_COMMAND(REG_DSTBY_ON_OFF);
    WRITE_DATA(0x00);
    
    WRITE_COMMAND(REG_DFRAME);
//    WRITE_DATA(0x00);        //60Hz
//    WRITE_DATA(0x01);        //75Hz
    WRITE_DATA(0x02);        //90Hz
//    WRITE_DATA(0x03);        //105Hz
//    WRITE_DATA(0x04);        //120Hz
//    WRITE_DATA(0x05);        //135Hz
//    WRITE_DATA(0x06);        //150Hz

    WRITE_COMMAND(REG_WriteDirection);
//    WRITE_DATA(0x00);        //RGB
    WRITE_DATA(0x08);        //BGR
    
    WRITE_COMMAND(REG_ScanDirection);
//    WRITE_DATA(0x00);        //
    WRITE_DATA(0x01);        //
    
    WRITE_COMMAND(REG_IF_Bus_Sel);
    WRITE_DATA(0x00);        //6bit interface bus
//    WRITE_DATA(0x01);        //8bit interface bus
//    WRITE_DATA(0x02);        //9bit interface bus
//    WRITE_DATA(0x03);        //16bit interface bus
//    WRITE_DATA(0x04);        //18bit interface bus

//    WRITE_COMMAND(REG_PeakDelay);
//    WRITE_DATA(0x00);
    
    WRITE_COMMAND(REG_PeakWidth);
    WRITE_DATA(0x03);
    WRITE_DATA(0x0F);
    WRITE_DATA(0x05);
    
    WRITE_COMMAND(REG_DotCurrent);
    WRITE_DATA(0x08);
    WRITE_DATA(0x0B);
    WRITE_DATA(0x02);
    WRITE_DATA(0x09);
    WRITE_DATA(0x0A);
    WRITE_DATA(0x0D);
    
//    WRITE_COMMAND(REG_PreC_Width);
//    WRITE_DATA(0x02);
    
    WRITE_COMMAND(REG_DDISP_ON_OFF); // Display ON/OFF SET
    WRITE_DATA(0x01); // Display OFF
}

void WRITE_COMMAND(unsigned char db_data)
{
    digitalWrite(A0B, HIGH);  //command
    PORTOLED = ~db_data;
    digitalWrite(CSB, HIGH);
    digitalWrite(WRB, HIGH);
    digitalWrite(WRB, LOW);
    digitalWrite(CSB, LOW);
}

void WRITE_DATA(unsigned char db_data)
{
    digitalWrite(A0B, LOW);  //parameter
    PORTOLED = ~db_data;
    digitalWrite(CSB, HIGH);
    digitalWrite(WRB, HIGH);
    digitalWrite(WRB, LOW);
    digitalWrite(CSB, LOW);
}

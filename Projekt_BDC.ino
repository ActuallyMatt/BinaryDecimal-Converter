#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MOSI   9
#define CLK   10
#define DC    11
#define CS    12
#define RESET 13
Adafruit_SSD1306 miniDisplay(MOSI, CLK, DC, RESET, CS);


const int x_pos = 100;   // X position of the rectangle
const int y_pos = 0;     // Y position of the rectangle
const int l = 27;        // length of the rectangle
const int h = 8;         // height of the rectangle
 
const byte zero_button = 3;  // digital input pin of the button for the "0"
const byte one_button = 4;   // digital input pin of the button for the "1"

byte x_cursor = 0;          // cursor of the binary code 

int bc[9];                  // array that store the "0" and "1" from the buttons
int bits[9];                // array that store the decimal number for 8 bit
int steps = 1;

byte onClickCounter = 0;    // counts how often the buttons gets clicked.

byte clicked_zb = 0;        // rise if the zero button is clicked
byte clicked_ob = 0;        // rise if the one button is clicked

bool state1;                // state of the zero button
bool state2;                // state of the one button

int xcursor;

int sum = 0;                // the decimal number of the binarycode

void setup() {
  pinMode(zero_button, INPUT_PULLUP);
  pinMode(one_button, INPUT_PULLUP);
  
  Serial.begin(9600);
  
  
  miniDisplay.begin();
  miniDisplay.clearDisplay();
  miniDisplay.drawRect(x_pos, y_pos, l, h, WHITE);
  miniDisplay.fillRect(103, 2, 21, 4, WHITE);
  
}

void loop() {

  buttons();
  clearDisp();
  
  if(bc[8]) {
    sum = bits[1]+bits[2]+bits[3]+bits[4]+bits[5]+bits[6]+bits[7]+bits[8];
    miniDisplay.setCursor(xcursor,19);
    miniDisplay.setTextSize(1);
    miniDisplay.println(sum);
  }
  miniDisplay.display();
}


void clearDisp() {
  if(state1 == LOW && state2 == LOW) {
    miniDisplay.clearDisplay();
    for(int i = 0;i<8;i++) {
      bc[i] = 0;
      bits[i] = 0;
    }
  }
}


void buttons() {
  state1 = digitalRead(zero_button);
  state2 = digitalRead(one_button);
  
  miniDisplay.setCursor(x_cursor,9);
  miniDisplay.setTextSize(1);
  miniDisplay.setTextColor(WHITE);
  
  if(state1 == LOW) {
    clicked_zb++;
    delay(200);
  }
  if(state2 == LOW) {
    clicked_ob++;
    delay(200);
  }
  
  
  if(clicked_zb == 2) {
    clicked_zb = 0;
    onClickCounter++;
    bc[onClickCounter] = 2;
    if(bc[onClickCounter] == 2) {
      bits[onClickCounter] = 0;
      miniDisplay.println("0");
       
    }
    x_cursor+=6;
  }
 
  
  if(clicked_ob == 2) {
    clicked_ob = 0;
    onClickCounter++;
    bc[onClickCounter] = 1;
    if(bc[onClickCounter] == 1) {
    
      switch(onClickCounter) {
        case 1: onClickCounter == 1;
                bits[onClickCounter] = 1;
                break;
        case 2: onClickCounter == 2;
                bits[onClickCounter] = 2;
                break;
        case 3: onClickCounter == 3;
                bits[onClickCounter] = 4;
                break;
        case 4: onClickCounter == 4;
                bits[onClickCounter] = 8;
                break;
        case 5: onClickCounter == 5;
                bits[onClickCounter] = 16;
                break;
        case 6: onClickCounter == 6;
                bits[onClickCounter] = 32;
                break;
        case 7: onClickCounter == 7;
                bits[onClickCounter] = 64;
                break;
        case 8: onClickCounter == 8;
                bits[onClickCounter] = 128;
                break;
      }
      
      miniDisplay.println("1"); 
      
    }
    x_cursor+=6;
  } 
  
}

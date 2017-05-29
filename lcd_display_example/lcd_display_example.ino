// lcd_display_example.ino
//
// David Hanley
// 29th May 2017
// 
// Displays text input from serial monitor (with scrolling if text longer than 16 chars) on the first line of 16x2 LCD display unit
// On second line displays number of seconds program has been running 
//
// Create circuit shown in instructions
// Connect Arduino to computer, transfer program and start serial monitor
// Input text (and send with a newline char)
// Text is displayed (scrolling if needed) on LCD display 

#include <LiquidCrystal.h>

// ARDUINO->LCD PIN mappings
const int D4_PIN = 9;
const int D5_PIN = 10;
const int D6_PIN = 11;
const int D7_PIN = 12;
const int RS_PIN = 7;
const int ENABLE_PIN = 8; 

const String SECONDS = " secs";
const int COLS = 16;
const int ROWS = 2;
const int SCROLL_TIME = 500;

String text = "Waiting for text from serial";     // text to display
LiquidCrystal lcd(RS_PIN,ENABLE_PIN,D4_PIN,D5_PIN,D6_PIN,D7_PIN);            // set up Arduino->LCD pin mappings

// code runs once
void setup() {
    Serial.begin(9600);
    lcd.begin(COLS,ROWS);              // initialise interface to LCD and set to 16 columns by 2 rows
    lcd.print(text);
    lcd.home();
}

// code runs in a continuous loop
void loop() {
  
  // check to see if any new serial input is available
  if(Serial.available()) {
    text = Serial.readStringUntil('\n');
    lcd.clear();
    lcd.print(text);
  }
  
  // scroll text, only if needed
  if (text.length() > COLS) {
    // move through text to display, dropping start chars one at a time and displaying what's left
    for(int currIndex = 0; currIndex < text.length() - COLS+1; currIndex++) {   
      String display = text.substring(currIndex);
      lcd.print(display);
      displayRunTime();       // also need to update run time displayed
      delay(SCROLL_TIME);
      lcd.clear();
    }
  }
  else {
    displayRunTime();
    delay(1000);
  }
  
}

// display how long program has been running in seconds on 2nd row of lcd display
void displayRunTime() {
  String runTime = String(millis() / 1000);
  runTime.concat(SECONDS);
  lcd.setCursor(0,1);       // move cursor to start of 2nd row
  lcd.print(runTime);
}


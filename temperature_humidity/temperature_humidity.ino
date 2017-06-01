// temperature_humidity.ino
//
// David Hanley
// 1st June 2017
// 
// Displays current temparature (C) and humidity on LCD read from a DHT11 sensor
// If button pressed display temp in F 
//
// Builds on the lcd_display_example.ino sketch

#include <LiquidCrystal.h>
#include <DHT.h>

// ARDUINO->LCD PIN mappings
#define D4_PIN 9
#define D5_PIN 10
#define D6_PIN 11
#define D7_PIN 12
#define RS_PIN 7
#define ENABLE_PIN 8
#define COLS 16
#define ROWS 2

// switch settings
#define SWITCH_PIN 3

// DHT sensor settings
#define DHT_PIN 2
#define DHT_TYPE DHT11

float temperature;
float humidity;
char units = 'C';

LiquidCrystal lcd(RS_PIN,ENABLE_PIN,D4_PIN,D5_PIN,D6_PIN,D7_PIN);      // initialise lcd instance
DHT dht(DHT_PIN, DHT_TYPE);                                            // initialise dht instance

// code runs once
void setup() {
    pinMode(SWITCH_PIN, INPUT_PULLUP); // set switch to pullup mode
    lcd.begin(COLS,ROWS);              // initialise interface to LCD and set to 16 columns by 2 rows
    lcd.print("Please wait ..");      
    lcd.home();
    dht.begin();                       // begin temp/humidity readings
}

// code runs in a continuous loop
void loop() {
  // wait at least two second between readings (as per sensor spec)
  delay(2000);

  // determine whether C or F
  if(digitalRead(SWITCH_PIN) == HIGH) {
    units = 'C';
  }
  else {
    units = 'F';
  }

  // get humidity and temparature
  humidity = dht.readHumidity();
  temperature = dht.readTemperature(units == 'F');
  if(isnan(temperature) || isnan(humidity)) {
    lcd.clear();
    lcd.print("Read Error. Retry");
  }
  else {
    // display temparature/hunidity
    display();
  }
}

// display temp/humidity
void display() {
  String temperatureStr = "Temp: ";
  String humidityStr = "Humidity: ";
  
  temperatureStr.concat(temperature);
  temperatureStr.concat(units);
  humidityStr.concat(humidity);
  humidityStr.concat("%");
  
  lcd.clear();
  lcd.print(temperatureStr);
  lcd.setCursor(0,1);
  lcd.print(humidityStr);
}


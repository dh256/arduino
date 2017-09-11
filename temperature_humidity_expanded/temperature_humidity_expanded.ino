// temperature_humidity_expanded.ino
//
// David Hanley
// 11th Sept 2017
// 
// Displays current temparature (C) and humidity on LCD read from a DHT22 sensor
//
// Builds on the temperature_humidity.ino sketch

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

// LED pin mappings
#define GREEN_LED_PIN 5
#define RED_LED_PIN 4
#define BLUE_LED_PIN 6
#define BLINK_DELAY 100

 // temp ranges
#define LOW_TEMP 18.5
#define HIGH_TEMP 21.0

// DHT sensor settings
#define DHT_PIN 2
#define DHT_TYPE DHT22

float temperature;
float humidity;
char units = 'C';

LiquidCrystal lcd(RS_PIN,ENABLE_PIN,D4_PIN,D5_PIN,D6_PIN,D7_PIN);      // initialise lcd instance
DHT dht(DHT_PIN, DHT_TYPE);                                            // initialise dht instance


// code runs once
void setup() {
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    testLeds();
    lcd.begin(COLS,ROWS);              // initialise interface to LCD and set to 16 columns by 2 rows
    lcd.print("Please wait ..");      
    lcd.home();
    dht.begin();                       // begin temp/humidity readings
}

// code runs in a continuous loop
void loop() {
  // wait at least two second between readings (as per sensor spec)
  delay(2000);

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
  
  tempLedIndicator();

  lcd.clear();
  lcd.print(temperatureStr);
  lcd.setCursor(0,1);
  lcd.print(humidityStr);
}

void tempLedIndicator() {
  if(temperature < LOW_TEMP) {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
  }
  else if (temperature > HIGH_TEMP) {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
  }
  else {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
  }
}

void testLeds() {
  for(int count = 0; count < 2; count++) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(BLINK_DELAY);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    delay(BLINK_DELAY);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(BLINK_DELAY);
    digitalWrite(BLUE_LED_PIN, LOW);
  }
}


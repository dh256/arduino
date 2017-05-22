// Simple traffic lights sequence
// David Hanley, May 2017
//
// User can select U (UK) or O (Other) to show country specific sequence
// Use SerialMonitor to send country to Arduino
//

int red_light_pin = 7;           // pin to use
int amber_light_pin = 8;
int green_light_pin = 9;

int hold_red = 3000;
int hold_red_amber = 1000;
int hold_green = 4000;
int hold_amber = 1000;

char country = 'O';

void setup() {
  // put your setup code here, to run once:

  // set up pins for outpyt
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(amber_light_pin, OUTPUT);

  // open serial port
  Serial.begin(9600);
  Serial.println("Enter country 'U' for UK; 'O' for OTHER: ");
  while (Serial.available() == 0) {}    // wait until a character is sent
  country = Serial.read();
  Serial.println("Starting sequence");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("STOP");
  digitalWrite(red_light_pin, HIGH);
  delay(hold_red);
  if (country == 'U') {         
    // UK uses red-amber - get ready to go
    Serial.println("GET READY TO GO");
    digitalWrite(amber_light_pin, HIGH);
    delay(hold_red_amber);
    digitalWrite(amber_light_pin, LOW);
  }
  digitalWrite(red_light_pin, LOW);
  Serial.println("GO");
  digitalWrite(green_light_pin, HIGH);
  delay(hold_green);
  Serial.println("GET READY TO STOP");
  digitalWrite(amber_light_pin, HIGH);
  digitalWrite(green_light_pin, LOW);
  delay(hold_amber);
  digitalWrite(red_light_pin, HIGH);
  digitalWrite(amber_light_pin, LOW);
}

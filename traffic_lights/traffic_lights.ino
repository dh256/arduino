// Simple traffic lights sequence
// David Hanley, May 2017

int red_light_pin = 7;           // pin to use
int amber_light_pin = 8;
int green_light_pin = 9;

int hold_red = 3000;
int hold_red_amber = 1000;
int hold_green = 4000;
int hold_amber = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(amber_light_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(red_light_pin, HIGH);
  delay(hold_red);
  digitalWrite(amber_light_pin, HIGH);
  delay(hold_red_amber);
  digitalWrite(red_light_pin, LOW);
  digitalWrite(amber_light_pin, LOW);
  digitalWrite(green_light_pin, HIGH);
  delay(hold_green);
  digitalWrite(amber_light_pin, HIGH);
  digitalWrite(green_light_pin, LOW);
  delay(hold_amber);
  digitalWrite(red_light_pin, HIGH);
  digitalWrite(amber_light_pin, LOW);
}

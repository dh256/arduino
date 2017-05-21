// Single blinking LED light
// David Hanley, May 2017

int pin = 7;           // pin to use
int blinkspeed = 500;  // blink speed

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin, HIGH);
  delay(blinkspeed);
  digitalWrite(pin, LOW);
  delay(blinkspeed);
}

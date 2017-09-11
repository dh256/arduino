# Temperature and Humidity (Expanded)

Sketch displays the current tempeature and humidity on a 16x2 LCD. Coloured LEDs are used to indicate acceptability of temperature.

- Red light: temp is too high
- Blue light: temp is too low
- Green light: temp is ok 

The _ok temperature range_ is harcoded (for now). In future will read from a web service.

Circuit Picture:
<To be completed>

Notes:
- Uses a Adafruit compatible DHT22 sensor. Will also work with the lower spec DHT11 sensor. For more information on DHT11/22 and associated libraries see: https://learn.adafruit.com/dht/overview 
- Builds on the _Temperature and Humidity_ sketch.
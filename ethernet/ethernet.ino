// ethernet.ino
// David Hanley, May 2017
//
// Starts Ethernet and displays IP address (on Serial) if one returned
// Requires UNO Ethernet shield (W5100 or equiavalent)
//
#include <Ethernet.h>

// variables
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};    // mac address for Ethernet shield

// functions
void maintainLease() {
  byte maintain = Ethernet.maintain();
    switch(maintain) {
      case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;

    case 2:
      //renewed success
      Serial.println("Renewed success");

      //print your local IP address:
      Serial.println(Ethernet.localIP());
      break;

    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;

    case 4:
      //rebind success
      Serial.println("Rebind success");

      //print your local IP address:
      Serial.println(Ethernet.localIP());
      break;

    default:
      //nothing happened
      break;
    }
}

// setup code
void setup() {
    Serial.begin(9600);
    Serial.println("Starting Ethernet. Please wait ...");  // may take up to 30 seconds, be patient
    if (Ethernet.begin(mac) == 0) {       
        Serial.println("Ethernet failed. Nothing else to do");
        for(;;)
        ;
    }

    Serial.println("Ethernet started!");
    Serial.print("IP address: ");
    Serial.println(Ethernet.localIP());
}

// loop code - runs repeatedly
void loop() {
    // add code here to deal with DHCP lease changes
    maintainLease();
}

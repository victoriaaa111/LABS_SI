#include <Arduino.h>
#include <string.h>   // strcmp

#include "Led.h"
#include "Serial.h"

#define LED_PIN 13

Led led(LED_PIN);

void setup() {
  serialInit(9600);
}

void loop() {
  char command[20];

  if (serialReadCommand(command, sizeof(command))) {

    if (strcmp(command, "led on") == 0) {
      led.turnOn();
      serialPrint("LED is now ON");
    }
    else if (strcmp(command, "led off") == 0) {
      led.turnOff();
      serialPrint("LED is now OFF");
    }
    else {
      serialPrint("Invalid command! Use 'led on' or 'led off'");
    }
  }
}

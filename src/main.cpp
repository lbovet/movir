#include <Arduino.h>
#include "IRremote.h"

#define SENSOR_PIN 16 // Sensor state input pin
#define LED_PIN_0 29
#define LED_PIN_1 30
#define LED_PIN_2 12
#define IR_PIN 3
static bool sensor_previous_state = false;

IRsend irsend;

void setup()
{
  pinMode(SENSOR_PIN, INPUT);  // PIR sensor pin as input
  pinMode(LED_PIN_0, OUTPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  digitalWrite(LED_PIN_0, LOW);
  digitalWrite(LED_PIN_1, HIGH);
  digitalWrite(LED_PIN_2, LOW);
  sensor_previous_state = digitalRead(SENSOR_PIN); // get sensor initial state (can be already true)
}

void loop()
{
  bool sensor_current_state = digitalRead(SENSOR_PIN);
  if ( sensor_previous_state == false   // looping until we detect a rising edge
       && sensor_current_state == true) { // when sensor state is trigged, it takes about 20 sec to recover
    digitalWrite(LED_PIN_1, LOW);
    for (int i = 0; i < 5; i++) {
      irsend.sendNEC(0x3EC1C936, 32);
      delay(50);
    }
    digitalWrite(LED_PIN_1, HIGH);
  }
  sensor_previous_state = sensor_current_state;
}

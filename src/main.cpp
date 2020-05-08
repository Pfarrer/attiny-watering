#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(PB0, PB1);

#include "button.c"
#include "adc.c"
#include "statemachine.cpp"

Statemachine statemachine(mySerial);

#include "timer.c"

volatile uint16_t moisture_value = 0;

void setup() {
    // Disable global interrupts for a init phase
    cli();

    mySerial.begin(9600);
    mySerial.println("Hello");

    statemachine.init();

    adc_init();
    timer_init();
    button_init();

    // Activate global interrupts again
    sei();
}

void loop() {
}

#include <Arduino.h>
#include <util/delay.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(PB0, PB1);

#include "button.c"
#include "pump.c"
#include "adc.c"

#include "statemachine.cpp"

Env env;
Statemachine statemachine(&env);

#include "timer.c"

void setup() {
    // Disable global interrupts for a init phase
    cli();

    mySerial.begin(9600);
    mySerial.println("Hello");

    statemachine.init();

    adc_init();
    timer_init();
    pump_init();
    button_init();

    // Activate global interrupts again
    sei();
}

void loop() {
}

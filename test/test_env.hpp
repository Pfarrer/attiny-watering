#ifndef TEST_ENV_H
#define TEST_ENV_H

#include "env.h"

class TestEnv : public Env {
public:
    void print(const char* s) {

    };
    void print(const char n) {

    };

    void disable_interrupts() {

    };
    void enable_interrupts() {
        
    };

    uint16_t adc_measure_value_averaged() {
        return 0;
    };
    bool button_is_pressed() {
        return false;
    };
    bool pump_is_active() {
        return false;
    };
    void pump_stop() {

    };
    void pump_start() {

    };
};

#endif
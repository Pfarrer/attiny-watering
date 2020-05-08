#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>

#define PRINT_EVERY_N_TICKS 8

struct Config {
    uint16_t button_pressed_tick_count = 0;
    uint16_t adc_value_drained = 0;
};

class State {
public:
    virtual ~State() {}

    virtual void serial_print(SoftwareSerial&) = 0;

    virtual State* on_timer_tick() {
        return this;
    };
};

class Statemachine {
private:
    SoftwareSerial& _softwareSerial;
    State* _state;
    uint8_t _last_print_tick_count = 0;
    
    void do_state_transition(State* next_state);

public:
    Statemachine(SoftwareSerial& softwareSerial) : _softwareSerial(softwareSerial) {};
    
    void init();

    void on_timer_tick();
};

class UninitializedState : public State {
private:
    Config* _config = new Config();

public:
    void serial_print(SoftwareSerial&);

    State* on_timer_tick();
};

class DrainingState: public State {
private:
    Config* _config;

public:
    void serial_print(SoftwareSerial&);

    State* on_timer_tick();

    DrainingState(Config* config) : _config(config) {};
};

#endif
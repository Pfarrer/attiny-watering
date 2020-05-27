#ifndef STATEMACHINE_H
#define STATEMACHINE_H

// #include <Arduino.h>
// #include <SoftwareSerial.h>

#include "env.h"

#define ADC_TOLERANCE 5
#define PRINT_EVERY_N_TICKS 1

struct Config {
    uint16_t button_pressed_tick_count = 0;
    uint16_t adc_value_drained = 0;
};

class State {
protected:
    Env& _env;

public:
    State(Env& env)
    : _env(env) {};

    virtual ~State() {}

    virtual const char* name() = 0;

    virtual Config* config() = 0;

    virtual void on_state_activation() {};

    virtual void on_state_deactivation() {};

    virtual State* on_timer_tick(uint16_t adc_value) {
        return this;
    };
};

class Statemachine {
private:
    Env& _env;

    State* _state;

    uint8_t _last_print_tick_count = 0;
    
    void do_state_transition(State* next_state);

public:
    Statemachine(Env& env)
    : _env(env) {};

    State* state() {
        return _state;
    };
    
    void init();

    void on_timer_tick();
};

class UninitializedState : public State {
public:
    UninitializedState(Env& env)
    : State(env) {};

    const char* name();

    Config* config();

    State* on_timer_tick(uint16_t adc_value);
};

class InitializingState : public State {
private:
    uint16_t _adc_value_drained;
    uint16_t _button_pressed_tick_count;

public:
    InitializingState(Env& env, uint16_t adc_value)
    : State(env)
    ,_adc_value_drained(adc_value)
    , _button_pressed_tick_count(0) {};

    const char* name();

    Config* config();

    void on_state_activation();

    void on_state_deactivation();

    State* on_timer_tick(uint16_t adc_value);
};

class WateredState : public State {
private:
    Config* _config;
    uint16_t _min_adc_value;

public:
    WateredState(Env& env, Config* config)
    : State(env)
    ,_config(config), _min_adc_value(1023) {};

    const char* name();

    Config* config();

    void on_state_activation();

    State* on_timer_tick(uint16_t adc_value);
};

class DrainingState: public State {
private:
    Config* _config;

public:
    DrainingState(Env& env, Config* config)
    : State(env)
    , _config(config) {};

    const char* name();

    Config* config();

    State* on_timer_tick(uint16_t adc_value);
};

#endif
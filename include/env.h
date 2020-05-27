#ifndef ENV_H
#define ENV_H

class Env {
public:
    virtual void print(const char* s) = 0;
    virtual void print(const char n) = 0;

    virtual void disable_interrupts() = 0;
    virtual void enable_interrupts() = 0;

    virtual uint16_t adc_measure_value_averaged() = 0;
    virtual bool button_is_pressed() = 0;
    virtual bool pump_is_active() = 0;
    virtual void pump_stop() = 0;
    virtual void pump_start() = 0;
};

#endif
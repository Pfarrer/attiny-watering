#include "statemachine.h"

void print_config(Config* config) {
    mySerial.print("Config: button_pressed_tick_count=");
    mySerial.print(config->button_pressed_tick_count);
    mySerial.print(", adc_value_drained=");
    mySerial.print(config->adc_value_drained);
    mySerial.print("\n");
}

////////////////////////////////////////////////////////////////////////////////
// Statemachine
////////////////////////////////////////////////////////////////////////////////

void Statemachine::init() {
    _state = new UninitializedState();
};

void Statemachine::do_state_transition(State* next_state) {
    if (next_state != _state) {
        auto previous_state = _state;
        this->_state = next_state;
        delete previous_state;
    }
};

void Statemachine::on_timer_tick() {
    if (_last_print_tick_count >= PRINT_EVERY_N_TICKS) {
        _last_print_tick_count = 0;
        this->_state->serial_print(this->_softwareSerial);
    } else {
        _last_print_tick_count++;
    }

    auto next_state = this->_state->on_timer_tick();
    do_state_transition(next_state);
};

////////////////////////////////////////////////////////////////////////////////
// Uninitialized State
////////////////////////////////////////////////////////////////////////////////

void UninitializedState::serial_print(SoftwareSerial& softwareSerial) {
  mySerial.print("UninitializedState: Moisture: ");
  mySerial.print(adc_measure_value_averaged());
  mySerial.print("\n");
};

State* UninitializedState::on_timer_tick() {
    if (button_is_pressed()) {
        if (_config->button_pressed_tick_count == 0) {
            _config->adc_value_drained = adc_measure_value_averaged();
        }

        _config->button_pressed_tick_count++;
    }
    else if (_config->button_pressed_tick_count > 0) {
        return new DrainingState(_config);
    }
    return this;
};

////////////////////////////////////////////////////////////////////////////////
// Draining State
////////////////////////////////////////////////////////////////////////////////

void DrainingState::serial_print(SoftwareSerial& softwareSerial) {
    mySerial.print("DrainingState: Moisture: ");
    mySerial.print(adc_measure_value_averaged());
    mySerial.print("\n");
};

State* DrainingState::on_timer_tick() {
    if (button_is_pressed()) {
        print_config(_config);
    }

    if (adc_measure_value_averaged() < _config->adc_value_drained) {
        
    }

    return this;
};

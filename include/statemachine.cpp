#include "statemachine.h"

void print_info(Env& env, uint16_t adc_value, State* state) {
    env.print("State=");
    env.print(state->name());
    env.print(", Moisture=");
    env.print(adc_value);
    env.print(", Pumping=");
    env.print(env.pump_is_active());

    if (state->config()) {
        env.print(" -- button_pressed_tick_count=");
        env.print(state->config()->button_pressed_tick_count);
        env.print(", adc_value_drained=");
        env.print(state->config()->adc_value_drained);
    }

    env.print("\n");
}

////////////////////////////////////////////////////////////////////////////////
// Statemachine
////////////////////////////////////////////////////////////////////////////////

void Statemachine::init() {
    _state = new UninitializedState(_env);
};

void Statemachine::do_state_transition(State* next_state) {
    if (next_state != _state) {
        _env.disable_interrupts();

        _env.print("PreviousState=");
        _env.print(_state->name());
        _env.print(", NextState=");
        _env.print(next_state->name());
        _env.print("\n");

        auto previous_state = _state;
        this->_state = next_state;
        previous_state->on_state_deactivation();
        next_state->on_state_activation();

        delete previous_state;
        
        _env.enable_interrupts();
    }
};

void Statemachine::on_timer_tick() {
    uint16_t adc_value = _env.adc_measure_value_averaged();
    if (_last_print_tick_count >= PRINT_EVERY_N_TICKS) {
        _last_print_tick_count = 0;
        print_info(this->_env, adc_value, this->_state);
    } else {
        _last_print_tick_count++;
    }

    auto next_state = this->_state->on_timer_tick(adc_value);
    do_state_transition(next_state);
};

////////////////////////////////////////////////////////////////////////////////
// Uninitialized State
////////////////////////////////////////////////////////////////////////////////

const char* UninitializedState::name() {
  return "Uninitialized";
};

Config* UninitializedState::config() {
  return NULL;
};

State* UninitializedState::on_timer_tick(uint16_t adc_value) {
    if (_env.button_is_pressed()) {
        return new InitializingState(_env, adc_value);
    }
    return this;
};

////////////////////////////////////////////////////////////////////////////////
// Initializing State
////////////////////////////////////////////////////////////////////////////////

const char* InitializingState::name() {
  return "Initializing";
};


Config* InitializingState::config() {
  return NULL;
};

void InitializingState::on_state_activation() {
    _env.pump_start();
};

void InitializingState::on_state_deactivation() {
    _env.pump_stop();
};

State* InitializingState::on_timer_tick(uint16_t adc_value) {
    if (_env.button_is_pressed()) {
        _button_pressed_tick_count++;
    }
    else {
        Config* config = new Config();
        config->adc_value_drained = _adc_value_drained;
        config->button_pressed_tick_count = _button_pressed_tick_count;

        return new WateredState(_env, config);
    }

    return this;
};

////////////////////////////////////////////////////////////////////////////////
// Watered State
////////////////////////////////////////////////////////////////////////////////

const char* WateredState::name() {
    return "Watered";
};

Config* WateredState::config() {
  return _config;
};

void WateredState::on_state_activation() {
    _min_adc_value = _env.adc_measure_value_averaged();
};

State* WateredState::on_timer_tick(uint16_t adc_value) {
    if (adc_value < _min_adc_value) {
        _min_adc_value = adc_value;
    } else if (adc_value > _min_adc_value + ADC_TOLERANCE) {
        return new DrainingState(_env, _config);
    }

    return this;
};


////////////////////////////////////////////////////////////////////////////////
// Draining State
////////////////////////////////////////////////////////////////////////////////

const char* DrainingState::name() {
    return "Draining";
};

Config* DrainingState::config() {
  return _config;
};

State* DrainingState::on_timer_tick(uint16_t adc_value) {
    if (adc_value > _config->adc_value_drained + ADC_TOLERANCE) {
        // TODO WATER
        return new WateredState(_env, _config);
    }

    return this;
};

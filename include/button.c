#define PIN_BUTTON PB2

volatile int8_t last_button_value = 0;

void button_init() {
    // Set data direction of button pin to out
    DDRB &= ~(1 << PIN_BUTTON);
    // And make sure, pull down resistor is set
    PORTB &= ~(1 << PIN_BUTTON);
}

bool button_is_pressed() {
    return PINB & (1 << PIN_BUTTON);
}
#define PIN_PUMP PB3

void pump_init() {
    // Set data direction of PUMP pin to out
    DDRB |= (1 << PIN_PUMP);
    // Turn PUMP off
    PORTB &= ~(1 << PIN_PUMP);
}

bool pump_is_active() {
    return PINB & (1 << PIN_BUTTON);;
}

void pump_start() {
    // On
    PORTB |= (1 << PIN_PUMP);
    _delay_ms(1);
    // Off
    PORTB &= ~(1 << PIN_PUMP);
    _delay_ms(9);
    
    // On
    PORTB |= (1 << PIN_PUMP);
    _delay_ms(3);
    // Off
    PORTB &= ~(1 << PIN_PUMP);
    _delay_ms(7);
    
    // On
    PORTB |= (1 << PIN_PUMP);
    _delay_ms(5);
    // Off
    PORTB &= ~(1 << PIN_PUMP);
    _delay_ms(5);
    
    // On
    PORTB |= (1 << PIN_PUMP);
    _delay_ms(7);
    // Off
    PORTB &= ~(1 << PIN_PUMP);
    _delay_ms(3);
    
    // On
    PORTB |= (1 << PIN_PUMP);
    _delay_ms(9);
    // Off
    PORTB &= ~(1 << PIN_PUMP);
    _delay_ms(1);
    
    // On
    PORTB |= (1 << PIN_PUMP);
    _delay_ms(10);
}

void pump_stop() {
    // Off
    PORTB &= ~(1 << PIN_PUMP);
    _delay_ms(1);
    // On
    PORTB |= (1 << PIN_PUMP);
    _delay_ms(9);

    // Off
    PORTB &= ~(1 << PIN_PUMP);
    _delay_ms(3);
    // On
    PORTB |= (1 << PIN_PUMP);
    _delay_ms(7);

    // Off
    PORTB &= ~(1 << PIN_PUMP);
    _delay_ms(5);
    // On
    PORTB |= (1 << PIN_PUMP);
    _delay_ms(5);

    // Off
    PORTB &= ~(1 << PIN_PUMP);
    _delay_ms(7);
    // On
    PORTB |= (1 << PIN_PUMP);
    _delay_ms(3);

    // Off
    PORTB &= ~(1 << PIN_PUMP);
    _delay_ms(9);
    // On
    PORTB |= (1 << PIN_PUMP);
    _delay_ms(1);

    // Off
    PORTB &= ~(1 << PIN_PUMP);
    _delay_ms(10);
}
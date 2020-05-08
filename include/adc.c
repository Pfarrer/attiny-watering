// ADC is defined to PB4 (ADC2)
#define ADC_MEASUREMENT_COUNT 5

void adc_init() {
    ADMUX =
        (0 << ADLAR) |     // left shift result
        (0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
        (0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
        (0 << MUX3)  |     // use ADC2 for input (PB4), MUX bit 3
        (0 << MUX2)  |     // use ADC2 for input (PB4), MUX bit 2
        (1 << MUX1)  |     // use ADC2 for input (PB4), MUX bit 1
        (0 << MUX0);       // use ADC2 for input (PB4), MUX bit 0

    ADCSRA =
        (1 << ADEN)  |     // Enable ADC
        (1 << ADPS2) |     // set prescaler to 16, bit 2
        (0 << ADPS1) |     // set prescaler to 16, bit 1
        (0 << ADPS0);      // set prescaler to 16, bit 0
}

uint16_t adc_measure_value() {
    // Start ADC measurement
    ADCSRA |= (1 << ADSC);

    // Wait till conversion complete
    while (ADCSRA & (1 << ADSC)) ;

    uint16_t result = ADCL | ADCH << 8;
    return result;
}

uint16_t adc_measure_value_averaged() {
    uint8_t n = ADC_MEASUREMENT_COUNT;
    float sum = 0;

    while (n--) {
        sum += adc_measure_value();
    }
    return sum / ADC_MEASUREMENT_COUNT;
}
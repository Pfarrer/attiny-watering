void timer_init() {
    // Set Watchdog Enable and Watchdog Change Enable
    WDTCR = (1 << WDE) | (1 << WDCE);

    WDTCR =
        (1 << WDIE) | // Set Watchdog Timeout Interrupt Enable
        (1 << WDP1) | // Set Prescaler to 0.125 s
        (1 << WDP0);  // Set Prescaler to 0.125 s
}

ISR(WDT_vect)
{
    statemachine.on_timer_tick();

    // Set Watchdog Timeout Interrupt Enable again
    WDTCR |= (1 << WDIE);
}
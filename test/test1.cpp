#include <unity.h>
#include <stdint.h>

#include "test_env.hpp"
#include "../include/statemachine.cpp"

TestEnv env;
Statemachine statemachine(env);

void test_function_calculator_addition(void) {
    statemachine.init();
    TEST_ASSERT_EQUAL_STRING(statemachine.state()->name(), "Uninitialized");
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_function_calculator_addition);
    UNITY_END();

    return 0;
}

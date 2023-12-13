#include "unity.h"

#include "module.h"

void setUp() {}
void tearDown() {}

void test_when_init_is_called_the_network_is_initialized(void) {
    TEST_ASSERT_EQUAL(module_add(1, 3), 1 + 3);
}

int main(void)
{
UNITY_BEGIN();
RUN_TEST(test_when_init_is_called_the_network_is_initialized);
return UNITY_END();
}

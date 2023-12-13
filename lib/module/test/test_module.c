#include "unity.h"

#include "module.h"

void setUp() {}
void tearDown() {}

void test_case_descriptive_name(void) {
    TEST_ASSERT_EQUAL(module_add(1, 3), 1 + 3);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_case_descriptive_name);
	return UNITY_END();
}

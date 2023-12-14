#include "unity.h"
#include "fff.h"
#include "module.h"

// MOCKS
DEFINE_FFF_GLOBALS;
FAKE_VOID_FUNC(void_function);
FAKE_VALUE_FUNC(int, int_function, int);

void setUp() {}
void tearDown() {}

void test_case_descriptive_name(void) {
	TEST_ASSERT_EQUAL(module_add(1, 3), 1 + 3);
}

void test_case_invoques_void_function(void) {
	module_uses_void_mock();
	TEST_ASSERT_EQUAL(void_function_fake.call_count, 1);
}

void test_case_mock_return_value(void) {
	int mock_return_value = 3;
	int mock_arg_value = 2;
	int_function_fake.return_val = mock_return_value;
	TEST_ASSERT_EQUAL(module_uses_value_and_args_mock(mock_arg_value), mock_return_value);
	TEST_ASSERT_EQUAL(int_function_fake.arg0_val, mock_arg_value);
	TEST_ASSERT_EQUAL(int_function_fake.call_count, 1);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_case_descriptive_name);
	RUN_TEST(test_case_invoques_void_function);
	RUN_TEST(test_case_mock_return_value);
	return UNITY_END();
}

#include "module.h"

int module_add(int a, int b) {
	return a + b;
}

void module_uses_void_mock() {
	void_function();
}

int module_uses_value_and_args_mock(int val) {
	return int_function(val);
}

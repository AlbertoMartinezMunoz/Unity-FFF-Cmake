#ifndef LIB_MODULE_INCLUDE_MODULE_H_
#define LIB_MODULE_INCLUDE_MODULE_H_

#include "module_mockable.h"

int module_add(int a, int b);

void module_uses_void_mock();

int module_uses_value_and_args_mock(int val);

#endif /* LIB_MODULE_INCLUDE_MODULE_H_ */

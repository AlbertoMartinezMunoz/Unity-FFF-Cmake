# Unity-FFF-Cmake
Example project for build Unity + Fake Function Framework unitary tests with CMake

## Requisites

### Unity

Unity test framework is a unitary testing framework designed in C and inttended for embedded software. It is added to the git repo as a git submodule, so **remember to clone this repository with the `--recurse-submodules` option.**

```console
git submodule add https://github.com/ThrowTheSwitch/Unity.git ./vendor/unity
```

Then, in the CMakeLists.txt of the project, we will include the unity subdirectory, but only when we compile the tests:

```cmake
if(UTEST)
	include(CTest)
	enable_testing()
	add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/fff")
endif()
```

### Fake Function Framework (FFF)

FFF is a micro-framework for creating fake C functions for tests. It is added to the git repo as a git submodule, so **remember to clone this repository with the `--recurse-submodules` option.**

```console
git submodule add https://github.com/meekrosoft/fff.git ./vendor/fff
```

Then, in the CMakeLists.txt of the project, we will include the fff subdirectory, but only when we compile the tests:

```cmake
if(UTEST)
	include(CTest)
	enable_testing()
	add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/unity")
	add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/fff")
endif()
```

### Valgrind

Valgrind is an instrumentation framework for building dynamic analysis tools. There are Valgrind tools that can automatically detect many memory management and threading bugs, and profile your programs in detail.

Valgrind will be using in the unitary testing to check there are not memory leaks.

```console
sudo apt-get update
sudo apt-get -y install valgrind
```

## Creating Unitary Tests

First we will create the source file for the tests, usually in a folder called `test` or similar. In that file we must include the unity framework and the header of the code we want to test.

```c
#include "unity.h"
#include "module.h"
```

Then, as we are using unity, we will define a setup and a teardown funtion which wll be executed before and after each test.

```c
void setUp() {}
void tearDown() {}
```

Then we will define the tests:

```c
void test_case_descriptive_name(void) {
    TEST_ASSERT_EQUAL(module_add(1, 3), 1 + 3);
}
```

At last, we will define a `main()` function wich will run the tests:

```c
int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_case_descriptive_name);
	return UNITY_END();
}
```

Then, we will create a `CMakeList.txt` in the test folder which will define the build of the tests.

The code we are going to test is defined as a library in the module's CMakeLists.txt file

```cmake
add_library(module ../src/module.c)  
target_include_directories(module PUBLIC ../include)
```

Then, we will create the test and we will link it with the library of the code to be tested.

```cmake
add_executable(test_module test_module.c)
target_link_libraries(test_module unity module)   
add_test(NAME test_module COMMAND test_module)
set_target_properties(test_module PROPERTIES FOLDER test)
```

### Adding Mocks

The code we are going to mock is defined as a library (module_mockable) in the mockable module's CMakeLists.txt file

```cmake
add_library(module_mockable src/module_mockable.c)  
target_include_directories(module_mockable PUBLIC include)
```

This code is linked in the module we are testing

```cmake
add_library(module src/module.c)  
target_include_directories(module PUBLIC include)
target_link_libraries(module module_mockable)
```

Then, when creating the test in CMakeLists.txt, we have to add also the `fff` lib.

```cmake
add_executable(test_module test_module.c)
target_link_libraries(test_module unity fff module)   
add_test(NAME test_module COMMAND test_module)
set_target_properties(test_module PROPERTIES FOLDER test)
```

In the testing code, we have to include the `fff`library and define the mocks we are going to use.

```c
#include "fff.h"
#include "module.h"

// MOCKS
DEFINE_FFF_GLOBALS;
FAKE_VOID_FUNC(void_function);
FAKE_VALUE_FUNC(int, int_function, int);
```

Then, we can test with the mocks following the fff [README.md](./vendor/fff/README.md) instructions:

```c
void test_case_mock_return_value(void) {
	int mock_return_value = 3;
	int mock_arg_value = 2;
	int_function_fake.return_val = mock_return_value;
	TEST_ASSERT_EQUAL(module_uses_value_and_args_mock(mock_arg_value), mock_return_value);
	TEST_ASSERT_EQUAL(int_function_fake.arg0_val, mock_arg_value);
	TEST_ASSERT_EQUAL(int_function_fake.call_count, 1);
}
```

## Build and Run

The unit tests will be launched using **ctest**

To build the unitary tests, first we launch CMake with the UTEST custom option and then make.

```console
cmake . -DUTEST=ON -H. -B buildtest
cd buildtest
make -j3
```

To launch **all** the tests:

```console
ctest -VV;
```

To launch only a testsuite:

```console
ctest -R "testsuite_name" -VV
```

To use **valgrind** for checking memory leaks:

```console
ctest -T memcheck -VV
```

All in one line:

```console
cmake . -DUTEST=ON -H. -B buildtest; cd buildtest; make -j3 && ctest -T memcheck -VV; cd ..
```

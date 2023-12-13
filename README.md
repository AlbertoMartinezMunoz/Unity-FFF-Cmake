# Unity-FFF-Cmake
Example project for build Unity + Fake Function Framework unitary tests with CMake

## Requisites

### Unity

Unity test framework is added to the git repo as a git submodule, so **remember to clone this repository with the `--recurse-submodules` option.**

```console
$ git submodule add https://github.com/ThrowTheSwitch/Unity.git ./vendor/unity
```

### Fake Function Framework (FFF)

### Valgrind

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

First, we will create a library with the code to be tested

```cmake
add_library(module ../src/module.c)  
target_include_directories(module PUBLIC ../include)
# Here we add the mocks
#target_link_libraries(module ${LIBS})
```

Then, we will create the test and we will link it with the library of the code to be tested.

```cmake
add_executable(test_module test_module.c)
target_link_libraries(test_module unity module)   
add_test(NAME test_module COMMAND test_module)
set_target_properties(test_module PROPERTIES FOLDER test)
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

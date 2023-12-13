# Unity-FFF-Cmake
Example project for build Unity + Fake Function Framework unitary tests with CMake

## Requisites

### Unity

### Fake Function Framework (FFF)

### Valgrind

Valgrind will be using in the unitary testing to check there are not memory leaks.

```console
sudo apt-get update
sudo apt-get -y install valgrind
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

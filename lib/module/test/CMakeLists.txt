# module
add_library(module ../src/module.c)  
target_include_directories(module PUBLIC ../include)
target_include_directories(module PUBLIC ../../module_mockable/include)
target_link_libraries(module fff)

# test_module
add_executable(test_module test_module.c)
target_link_libraries(test_module unity module)   
add_test(NAME test_module COMMAND test_module)
set_target_properties(test_module PROPERTIES FOLDER test)

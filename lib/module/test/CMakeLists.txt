# test_module
add_executable(test_module test_module.c)
target_link_libraries(test_module unity fff module)   
add_test(NAME test_module COMMAND test_module)
set_target_properties(test_module PROPERTIES FOLDER test)
if(BUILD_TESTING)
	add_subdirectory(test)
endif()

# module
add_library(module src/module.c)  
target_include_directories(module PUBLIC include)
target_link_libraries(module module_mockable)
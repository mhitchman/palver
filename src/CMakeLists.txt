# PALVERLIB
add_subdirectory(palverlib)

# PALV
add_executable(palv
	main.cpp)
target_compile_features(palv PRIVATE cxx_std_17)
set_property(TARGET palv PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET palv PROPERTY CXX_EXTENSIONS OFF)

target_compile_options(palv PRIVATE ${custom_compile_options})

target_link_libraries(palv PRIVATE
	palvlib
	Clara::Clara)

install(TARGETS palv DESTINATION bin)

# TESTS
if (ENABLE_TESTS)
   add_subdirectory(tests)
endif()

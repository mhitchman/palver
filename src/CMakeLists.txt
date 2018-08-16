add_subdirectory(tests)

# PALVLIB
add_library(palvlib STATIC
	palv.cpp)

target_compile_features(palvlib PUBLIC cxx_std_17)
target_compile_options(palvlib PRIVATE ${custom_compile_options})
target_link_libraries(palvlib PUBLIC
	stdc++fs)
target_include_directories(palvlib PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)

# PALV
add_executable(palv
	main.cpp)
target_compile_features(palv PRIVATE cxx_std_17)
set_property(TARGET palv PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET palv PROPERTY CXX_EXTENSIONS OFF)

target_compile_options(palv PRIVATE ${custom_compile_options})

target_include_directories(palv PRIVATE ${THIRD_PARTY_INCLUDES})

target_link_libraries(palv
	palvlib)

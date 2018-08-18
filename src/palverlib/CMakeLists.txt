add_library(palvlib STATIC
	palv.cpp)

target_compile_features(palvlib PUBLIC cxx_std_17)
target_compile_options(palvlib PRIVATE ${custom_compile_options})
target_link_libraries(palvlib PUBLIC
	stdc++fs)
target_include_directories(palvlib PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)

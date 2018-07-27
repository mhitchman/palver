add_executable(palv
	main.cpp)

set_property(TARGET palv PROPERTY CXX_STANDARD 17)
set_property(TARGET palv PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET palv PROPERTY CXX_EXTENSIONS OFF)

target_link_libraries(palv stdc++fs)

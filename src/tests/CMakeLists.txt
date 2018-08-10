project(testlib)

add_executable(testlib
	testMain.cpp
	test_palv.cpp)

target_link_libraries(testlib
	PRIVATE
	Catch2::Catch2
	palvlib)

include(Catch)
catch_discover_tests(testlib)


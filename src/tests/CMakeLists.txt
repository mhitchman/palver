project(testlib)

add_executable(testlib
	testMain.cpp
	test_palv.cpp)

target_link_libraries(testlib
	PRIVATE
	Catch2::Catch2
	palvlib
	stdc++fs)

add_custom_command(TARGET testlib POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
		   ${CMAKE_CURRENT_SOURCE_DIR}/testConf $<TARGET_FILE_DIR:testlib>/testConf)

include(Catch)
catch_discover_tests(testlib)

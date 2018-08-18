if(ENABLE_TESTS)
	# Only want Catch2 as a subproject if we're building tests
	add_subdirectory(Catch2)

	#Make the Catch provided modules available to the rest of the project
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Catch2/contrib/" PARENT_SCOPE)
endif()

add_subdirectory(Clara)

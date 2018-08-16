add_subdirectory(Catch2)

include(GNUInstallDirs)

#Make the Catch provided modules available to the rest of the project
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Catch2/contrib/" PARENT_SCOPE)
set(THIRD_PARTY_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/includes" PARENT_SCOPE)


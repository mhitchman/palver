# Download Clara header file
file(DOWNLOAD https://github.com/catchorg/Clara/releases/download/v1.1.4/clara.hpp
	      ${CMAKE_CURRENT_SOURCE_DIR}/clara.hpp
	      EXPECTED_HASH MD5=dd92f20a27ab40b3c8f7e387020e23e4)

add_library(clara INTERFACE)
target_include_directories(clara INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_library(Clara::Clara ALIAS clara)

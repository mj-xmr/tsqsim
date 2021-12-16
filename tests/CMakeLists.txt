cmake_minimum_required(VERSION 3.5.1)

add_subdirectory(test-common)
add_subdirectory(test-base)
add_subdirectory(test-tsqsim)
if (BUILD_QT)
	add_subdirectory(qt-test)
endif()

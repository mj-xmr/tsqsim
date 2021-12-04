cmake_minimum_required(VERSION 3.5.1)

add_subdirectory(lib-base)
if (NOT APPLE) # TODO: Temporary
	add_subdirectory(tsqsim)
endif()
add_subdirectory(tsqsim-lib)

if (BUILD_QT)
	add_subdirectory(qt-lib)
	add_subdirectory(tsqsim-qt)
endif()

cmake_minimum_required(VERSION 3.5.1)

add_subdirectory(lib-base)
add_subdirectory(tsqsim-lib)

if (BUILD_WX)
	add_subdirectory(wxConfQT)
endif()

add_subdirectory(tsqsim)

if (BUILD_QT)
	add_subdirectory(qt-lib)
	add_subdirectory(tsqsim-qt)
endif()

cmake_minimum_required(VERSION 3.5.1)

add_subdirectory(lib-base)
add_subdirectory(tsqsim-lib)

# TODO: Don't build with NO_WS
add_subdirectory(wxConfQT)

add_subdirectory(tsqsim)

if (BUILD_QT)
	add_subdirectory(qt-lib)
	add_subdirectory(tsqsim-qt)
endif()

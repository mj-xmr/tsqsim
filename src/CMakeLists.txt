cmake_minimum_required(VERSION 3.5.1)

add_subdirectory(lib-base)
add_subdirectory(tsqsim)
add_subdirectory(tsqsim-lib)

# TODO: Don't build with NO_QT
add_subdirectory(qt-lib)
add_subdirectory(tsqsim-qt)

cmake_minimum_required(VERSION 3.5.1)

add_subdirectory(test-common)
add_subdirectory(test-base)

# TODO: Don't build with NO_QT
add_subdirectory(qt-test)


# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
cmake_minimum_required(VERSION 3.5.1)
include(../../cmake/util.cmake)
project( test-common )
find_package(UnitTest++)

# https://github.com/unittest-cpp/unittest-cpp/wiki/Macro-and-Parameter-Reference # TODO

file( GLOB SRCS src/*.cpp */*.h */*.hpp)

add_library (${PROJECT_NAME} ${LINK_TYPE} ${SRCS})

enjoSetupTarget(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${UTPP_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE /usr/local/lib)
target_link_libraries(${PROJECT_NAME} UnitTest++)

enjo_target_pch(${PROJECT_NAME} src/pch_test.h)

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/bin/lib)


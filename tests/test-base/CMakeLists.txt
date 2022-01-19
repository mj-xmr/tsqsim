# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
cmake_minimum_required(VERSION 3.5.1)
include(../../cmake/util.cmake)
include(../../cmake/stock-includes.cmake)
project( test-base )

file( GLOB SRCS src/*.cpp */*.h */*.hpp)

add_executable(${PROJECT_NAME} ${SRCS})
add_test(${PROJECT_NAME} ${PROJECT_NAME})
enjoSetupTarget(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} lib-base test-common)

enjo_target_unity(${PROJECT_NAME})
# A hack to make the tests run around OptiVar
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	       COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/static/opti-release
)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

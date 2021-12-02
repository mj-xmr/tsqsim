# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
cmake_minimum_required(VERSION 3.5.1)
project(qt-lib)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
SET(CMAKE_INSTALL_RPATH "lib")


file( GLOB SRCS src/*.cpp */*.hpp */*.h)

add_library(${PROJECT_NAME} ${LINK_TYPE} ${SRCS})

enjoSetupTarget(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} lib-base Qt5::Widgets qcustomplot)

enjo_target_pch(${PROJECT_NAME} src/pch_qt.h)
enjo_target_unity(${PROJECT_NAME})

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/bin)


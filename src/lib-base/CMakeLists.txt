# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
cmake_minimum_required(VERSION 3.5.1)
include(../../cmake/util.cmake)
project( lib-base )

file( GLOB SRCS src/*.cpp */*.h */*.hpp)

option(WITH_FEATURE_URT 	"Use URT" ON)

add_library (${PROJECT_NAME} ${LINK_TYPE} ${SRCS})
if (WITH_FEATURE_URT)
	target_compile_definitions(${PROJECT_NAME} PRIVATE -DUSE_URT)
	set (EXTRA_LIBS ${EXTRA_LIBS} URT)
endif()
enjoSetupTarget(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} EnjoLibBoost FuzzyEngine++ ${EXTRA_LIBS})
enjo_target_pch(${PROJECT_NAME} src/pch_base.h)
#enjoCopyFile(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../run-tests.sh ../run-tests.sh)
#enjoCopyFile(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../libs-base.sh ../libs-base.sh)
#enjoCopyFile(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../libs-stock.sh ../libs-stock.sh)

enjoRunUTs(${PROJECT_NAME})

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/bin/lib)

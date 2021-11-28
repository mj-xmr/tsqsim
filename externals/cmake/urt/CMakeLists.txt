cmake_minimum_required(VERSION 3.5.1)

include(../../../cmake/util.cmake)
project(URT)

#find_package(Eigen3 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIRS})
find_package(Armadillo)

set(BASE_DIR ../../URT)

file( GLOB SRCS ${BASE_DIR}/src/*.cpp ${BASE_DIR}/*/*.h ${BASE_DIR}/*/*.hpp)

add_library (${PROJECT_NAME} ${LINK_TYPE} ${SRCS})
enjoSetupTarget(${PROJECT_NAME})
enjo_target_unity(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} armadillo ${ARMADILLO_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE USE_ARMA) # TODO: USE_EIGEN here
# TODO: Use Eigen
# TODO: Use MKL
# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (${PROJECT_NAME} PUBLIC ${BASE_DIR}/include)
install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/bin/lib)


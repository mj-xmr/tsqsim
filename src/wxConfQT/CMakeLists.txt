# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
cmake_minimum_required(VERSION 3.5.1)
include(../../cmake/util.cmake)

project(wxConf)
SET(CMAKE_INSTALL_RPATH "lib")

#message(FATAL_ERROR "${CMAKE_CURRENT_SOURCE_DIR}")
#find_package(wxWidgets COMPONENTS core base REQUIRED)

set (WX_COMPS "core base")
#message(FATAL_ERROR "${CMAKE_CURRENT_SOURCE_DIR}")
if (BUILD_MINGW)
else()
	if (WIN32)
		message(STATUS "Config wx for Windows")
		set(wxWidgets_EXCLUDE_COMMON_LIBRARIES TRUE)
		#set(wxWidgets_CONFIG_OPTIONS --static)
	endif()
	find_package(wxWidgets COMPONENTS ${WX_COMPS} REQUIRED)
	include(${wxWidgets_USE_FILE})
	#message(FATAL_ERROR ${wxWidgets_USE_FILE})
endif()

file( GLOB SRCS src/*.cpp */*.h */*.hpp)

add_executable(${PROJECT_NAME} ${SRCS})
enjoSetupTarget(${PROJECT_NAME})
#target_link_libraries(${PROJECT_NAME} multi-tf-lib wx ${wxWidgets_LIBRARIES})
target_link_libraries(${PROJECT_NAME} lib-base wx )

enjo_target_pch(${PROJECT_NAME} src/wx_pch.h)
enjo_target_unity(${PROJECT_NAME})

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/bin)

#${CMAKE_CURRENT_SOURCE_DIR}/../prep-env.sh
#add_custom_command(TARGET ${PROJECT_NAME}
    #    POST_BUILD
#        WORKING_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..
#        COMMAND "ls ${CMAKE_CURRENT_SOURCE_DIR}"
   #     COMMAND bash "cd ${CMAKE_BINARY_DIR} && ${CMAKE_CURRENT_SOURCE_DIR}/../prep-env.sh"
   #     )
   
#enjoCreateSymlinks2Data(${PROJECT_NAME})
#set(DIR_CFG ~/devel/progs-lc/progs-build/cfg) # Keeps the config across reboots
#enjoSymlink(${PROJECT_NAME} ${DIR_CFG} cfg)
#file(MAKE_DIRECTORY ${DIR_CFG})
#install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/bin)


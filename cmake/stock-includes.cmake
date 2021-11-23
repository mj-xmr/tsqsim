# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
cmake_minimum_required(VERSION 3.5.1)

#include_directories("~/devel/lib/dlib-current")
#include_directories("~/devel/lib/tree/include")
#link_directories("~/devel/lib/tree/lib")

set( home $ENV{HOME})

function (enjoCreateSymlinksCfg projName)
    enjoSymlink(${projName} ../wxConfQT/cfg cfg)
endfunction()

function (enjoCreateSymlinksStatic projName)
    enjoSymlink(${projName} ../multi-tf-lib/static static)
endfunction()

function (enjoCreateSymlinks2Data projName)
    enjoSymlink(${projName} ../multi-tf/data data)
endfunction()

function (enjoCreateSymlinksData projName)
    enjoSymlink(${projName} ${home}/temp/forex data)
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${home}/temp/forex bin/data)")
endfunction()


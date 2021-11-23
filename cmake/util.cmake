
#option(USE_RELEASE 	"Use MinSizeRel" ON)
option(USE_STATIC 	"Use static linkage" OFF)
option(USE_LTO 		"Use global LTO"   OFF)
option(USE_TESTS 	"Run tests while building" OFF)
option(USE_OPTI_O3 	"Use O3" ON)
option(USE_OPTI_O0 	"Use O0" OFF)
option(USE_OPTI_NATIVE 	"Use native build" OFF)
option(USE_OPTI_GENERIC	"Use generic build" OFF)
option(USE_DEBUG 	"Use Debug" OFF)
option(USE_DEP_TREE 	"Use Dep Tree -H" OFF)
option(USE_CCACHE 	"Use CCache" ON)
option(USE_COMPIL_PROFILER "Use compilation profiling (Clang)" OFF)


cmake_host_system_information(RESULT HOST_NAME QUERY HOSTNAME)
function (enjoMessage text)
	message("${HOST_NAME}	${text}")
endfunction()

function (enjoWarning text)
	message(WARNING "${HOST_NAME}	${text}")
endfunction()

function (enjoError text)
	message(FATAL_ERROR "${HOST_NAME}	${text}")
endfunction()


if (USE_LTO)
	# https://stackoverflow.com/a/47370726
	cmake_policy(SET CMP0069 NEW)
	set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
	# Global LTO works better than individual
endif()

if (USE_STATIC)
	set (LINK_TYPE STATIC)
else()
	set (LINK_TYPE SHARED)
	if (USE_LTO)
		enjoWarning("LTO works best with USE_STATIC=ON")
	endif()
endif()

if(${CMAKE_VERSION} VERSION_LESS "3.16.6") 
	enjoWarning("Please consider to switch to CMake 3.16.6 or above")
else()
	option(USE_PCH		"Use native PCH" OFF})
	option(USE_PCH_AGGRESS	"Use native PCH agressively" OFF)
	option(USE_UNITY 	"Use unity builds" ON)
endif()

macro (enjo_target_unity target)
	if (USE_UNITY)
		set_target_properties(${target} PROPERTIES UNITY_BUILD "TRUE")
	endif()
endmacro()

# TODO: Make speed tests
macro (enjo_target_pch target pch)
	if (USE_PCH)
		enjo_target_pch_internal(${target} ${pch})
	endif()
endmacro()

macro (enjo_target_pch_agress target)
	if (USE_PCH)
		if (USE_PCH_AGGRESS)
			enjo_target_pch_internal(${target} ${pch})
			target_compile_options(${target} PRIVATE "-fpch-preprocess")
		endif()
	endif()
endmacro()

macro (enjo_target_pch_internal target pch)
	target_precompile_headers(${target} PRIVATE ${pch}) # Might be slower. Interferes with ccache
endmacro()

#if (USE_RELEASE)
#	set(CMAKE_CONFIGURATION_TYPES "MinSizeRel" CACHE STRING "" FORCE)
#endif()
if (USE_DEBUG)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif()

if (USE_OPTI_O3)
	add_compile_options("-O3")
	#add_compile_options("-flto") # Breaks multi-tf-test in dynamic linkage
else()
    if (USE_OPTI_O0)
    	add_compile_options("-O0")
    endif()
endif()
if (USE_OPTI_NATIVE)
	add_compile_options("-march=native")
	add_compile_options("-funsafe-math-optimizations") # For RPi
else()
    if (USE_OPTI_GENERIC)
    	add_compile_options("-mtune=generic")
    endif()
endif()

if (USE_DEP_TREE)
	add_compile_options("-H")
endif()

if (USE_COMPIL_PROFILER)
	add_compile_options("-ftime-trace")
else()
	if (USE_CCACHE)
		find_program(CCACHE_FOUND ccache)
		if (CCACHE_FOUND)
		    #message("ccache found")
		    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
		    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK    ccache)
		else()
		    message("ccache NOT found!")
		endif(CCACHE_FOUND)
	endif()
endif()

macro (SetupCotire target)
endmacro()

function (enjoSetupTarget target)
	set_target_properties("${target}" PROPERTIES LINK_FLAGS_RELEASE -s)
	set_target_properties("${target}" PROPERTIES LINK_DEPENDS_NO_SHARED true)
endfunction()

function (enjoCopyFile projName source dest)
	add_custom_command(TARGET ${projName} POST_BUILD
	       COMMAND ${CMAKE_COMMAND} -E copy
	       ${source}
	       $<TARGET_FILE_DIR:${projName}>/${dest}
	)
endfunction()

function (enjoCopyDir projName source dest)
	add_custom_command(TARGET ${projName} POST_BUILD
	       COMMAND ${CMAKE_COMMAND} -E copy_directory
	       ${source}
	       $<TARGET_FILE_DIR:${projName}>/${dest}
	)
endfunction()

function (enjoSymlink projName linkSrc linkDst)
    add_custom_command(TARGET ${projName} POST_BUILD
       COMMAND ${CMAKE_COMMAND} -E create_symlink ${linkSrc} ${linkDst}
       )
    #install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${target} bin/${link})")
endfunction()
function (enjoSymlinkData projName)
	enjoSymlink(${projName} ${CMAKE_CURRENT_SOURCE_DIR}/data data)
endfunction()
function (enjoSymlinkCfg projName)
	enjoSymlink(${projName} ${CMAKE_CURRENT_SOURCE_DIR}/cfg cfg)
endfunction()

function (enjoCopyFollowSymlinks source dest)
	execute_process (
	    COMMAND bash -c "pwd; cp -vLr ${source} ${dest}; pwd" 
)
endfunction()

function (enjoRunUTs projName)
 if (USE_TESTS)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
       		COMMAND mkdir -p cfg
        )
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
       		COMMAND ../run-tests.sh
       		#WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
       	)
       	endif()
endfunction()    

#set(CMAKE_C_COMPILER 	/usr/lib/icecc/bin/gcc)
#set(CMAKE_CXX_COMPILER 	/usr/lib/icecc/bin/g++) 

#add_compile_options("-std=c++11") # Breaks PCH
#add_compile_options("-std=gnu++11")
add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=gnu++11>") # Only for C++
# https://crascit.com/2015/03/28/enabling-cxx11-in-cmake/
#add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=gnu++14>") # C++ 14 needed only for URT

add_compile_options("-ffast-math")
add_compile_options("-Winvalid-pch")

#add_compile_options("-ftime-report")
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("~/devel/lib/tree/include")
link_directories("~/devel/lib/tree/lib")


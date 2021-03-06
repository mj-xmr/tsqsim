include(util)

option(BUILD_QT    "Build QT apps"  ON)

function (tsqSetupSymlinks target)
	# TODO: use a loop for [data, cfg, scripts]
	enjoSymlink(${target} ../../data 	${CMAKE_BINARY_DIR}/bin/data)	# Common data dir
	enjoSymlink(${target} ../../cfg  	${CMAKE_BINARY_DIR}/bin/cfg)	# Common cfg  dir
	enjoSymlink(${target} ../../static    	${CMAKE_BINARY_DIR}/bin/static)	# Common static dir
	enjoSymlink(${target} ../../../data   ${CMAKE_CURRENT_BINARY_DIR}/data)	# Common data dir
	enjoSymlink(${target} ../../../cfg    ${CMAKE_CURRENT_BINARY_DIR}/cfg)	# Common cfg  dir
	enjoSymlink(${target} ../../../static ${CMAKE_CURRENT_BINARY_DIR}/static)	# Common static dir
endfunction()


function (tsqSetupDirStatic target)
	# A hack to make the tests run around OptiVar
	add_custom_command(TARGET ${target} POST_BUILD
		       COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/static/opti-release
	)
endfunction()

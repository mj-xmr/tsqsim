include(util)

function (tsqSetupSymlinks target)
	# TODO: use a loop for [data, cfg, scripts]
	enjoSymlink(${target} ../../data 	${CMAKE_BINARY_DIR}/bin/data)	# Common data dir
	enjoSymlink(${target} ../../cfg  	${CMAKE_BINARY_DIR}/bin/cfg)	# Common cfg  dir
	enjoSymlink(${target} ../../scripts ${CMAKE_BINARY_DIR}/bin/scripts)	# Common data dir
	enjoSymlink(${target} ../../../data ${CMAKE_CURRENT_BINARY_DIR}/data)	# Common data dir
	enjoSymlink(${target} ../../../cfg  ${CMAKE_CURRENT_BINARY_DIR}/cfg)	# Common cfg  dir
	enjoSymlink(${target} ../../../scripts ${CMAKE_CURRENT_BINARY_DIR}/scripts)	# Common data dir
endfunction()


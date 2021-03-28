
function(sdk_add_subdirectory INPUT_LIST DIRECTORY)
add_subdirectory(${DIRECTORY})
set(INPUT_SOURCES ${${INPUT_LIST}})
set(TEMP_SOURCES "")
foreach(entry ${SOURCES})
  list(APPEND TEMP_SOURCES ${DIRECTORY}/${entry})
endforeach()
list(APPEND TEMP_SOURCES ${INPUT_SOURCES})
set(${INPUT_LIST} ${TEMP_SOURCES} PARENT_SCOPE)
endfunction()


function(sdk_add_base_executable
		TARGET
		SOURCES
		INCLUDE_DIRECTORIES
		CPU_OPTIONS
		DEFINITIONS
		LINKER_FILE)

	message("SOURCE " ${SOURCES})
	add_executable(${TARGET})
	target_sources(${TARGET}
		PRIVATE
		${SOURCES}
		)

	target_include_directories(${TARGET}
		PRIVATE
		${INCLUDE_DIRECTORIES}
		src
		)

	target_compile_options(${TARGET}
		PRIVATE
		${CPU_OPTIONS}
		-Os
		$<$<COMPILE_LANGUAGE:CXX>:-Wno-register>
		-fdata-sections -ffunction-sections
		)

	target_compile_definitions(${TARGET}
		PRIVATE
		${DEFINITIONS}
		)

	target_link_libraries(${TARGET}
		PRIVATE
		c m nosys
		)

	target_link_options(${TARGET}
		PRIVATE
		${CPU_OPTIONS}
		-specs=nano.specs
		-T${LINKER_FILE}
		-Wl,--gc-sections,--print-memory-usage)


	set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 17)
	target_compile_options(${TARGET}
		PRIVATE
		-O3
		)

endfunction()

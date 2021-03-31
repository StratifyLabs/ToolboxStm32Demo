
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

	add_custom_target(
		asm_${TARGET} ALL
		DEPENDS ${TARGET}
		COMMAND ${CMAKE_OBJDUMP} -S -j .text -j .data -j .isr_vector -d ${CMAKE_CURRENT_BINARY_DIR}/${TARGET} > ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}.lst)

	add_custom_target(
		bin_${TARGET} ALL
		DEPENDS ${TARGET}
		COMMAND ${CMAKE_OBJCOPY}  -j .isr_vector -j .text -j .rodata -j .ARM.extab -j .ARM -j .preinit_array -j .init_array -j .fini_array -j .data -O binary ${CMAKE_CURRENT_BINARY_DIR}/${TARGET} ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}.bin)



endfunction()

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
# Avoid repeating the IF statement in the ENDIF and ELSE
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

# lightweight cpp helpers
project(lch)

# includ lch/include
include_directories("include")

# automatically add lch/test/*.cpp
file(GLOB all_cpp_files
	test/*.cpp
)

foreach(cpp_file ${all_cpp_files})
	get_filename_component(cpp_file_name ${cpp_file} NAME_WE)
	set(app_name ${cpp_file_name})
	message(STATUS "Adding " ${app_name} "=" ${cpp_file})
	add_executable(${app_name} ${cpp_file})
	install(TARGETS ${app_name} DESTINATION ${CMAKE_SOURCE_DIR}/bin)
endforeach()

# install additional files
file(GLOB all_cfg_files
	test/*.cfg
)
install(FILES ${all_cfg_files} DESTINATION ${CMAKE_SOURCE_DIR}/bin)
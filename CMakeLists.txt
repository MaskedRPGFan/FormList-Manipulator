cmake_minimum_required(VERSION 3.22)

project(
    FormListManipulator
    VERSION 1.5.0
    LANGUAGES CXX
    DESCRIPTION "Allows dynamic modification of FormLists."
)
set(PROJECT_FRIENDLY_NAME "Formlist Manipulator")
set(PROJECT_AUTHOR "MaskedRPGFan")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Plugin.hpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.hpp
    @ONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.rc
    @ONLY
)

find_package(binary_io CONFIG REQUIRED)
find_package(CommonLibSSE CONFIG REQUIRED)
find_package(xbyak CONFIG REQUIRED)
find_path(SIMPLEINI_INCLUDE_DIRS "ConvertUTF.c")
find_path(MERGEMAPPER_INCLUDE_DIRS "MergeMapperPluginAPI.h")

add_library(
    ${PROJECT_NAME}
    SHARED
    src/main.cpp
    src/Plugin.hpp
    ${CMAKE_CURRENT_BINARY_DIR}/version.rc
	${MERGEMAPPER_INCLUDE_DIRS}/MergeMapperPluginAPI.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE CommonLibSSE::CommonLibSSE)
target_link_libraries(${PROJECT_NAME} PRIVATE xbyak::xbyak)
target_include_directories(${PROJECT_NAME} PRIVATE ${SIMPLEINI_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PRIVATE ${MERGEMAPPER_INCLUDE_DIRS})

set(MOD_FOLDER "$ENV{SKSE_SKYRIM_SE_MODS}/${PROJECT_NAME} - DEV")
set(DLL_FOLDER "${MOD_FOLDER}/SKSE/Plugins")

# Create output directory if it does not exist
add_custom_command(
	TARGET "${PROJECT_NAME}"
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E make_directory "${DLL_FOLDER}"
	#COMMAND "${CMAKE_COMMAND}" -E make_directory "${MOD_FOLDER}/Scripts"
	VERBATIM
)

# Copy the output .dll and scripts to the configured output directory
add_custom_command(
	TARGET "${PROJECT_NAME}"
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${DLL_FOLDER}"
	#COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Scripts" "${MOD_FOLDER}/Scripts"
	VERBATIM
)

# Copy .esp .esm .esl files, if present (at prepare time)
file(GLOB PLUGIN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.esp" "${CMAKE_CURRENT_SOURCE_DIR}/*.esm" "${CMAKE_CURRENT_SOURCE_DIR}/*.esl")
if(PLUGIN_FILES)
	add_custom_command(
		TARGET "${PROJECT_NAME}"
		POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy_if_different ${PLUGIN_FILES} "${MOD_FOLDER}"
		VERBATIM
	)
endif()

cmake_minimum_required(VERSION 3.8)

project(SQLCore VERSION 0.2.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(SQLC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SQLC_SRC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>")
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb/$<CONFIG>")

if(BUILD_PLUGINS_ONLY)
    message(WARNING "Build factory is disable.")
else()
    message(STATUS "Build factory is enable.")
    add_subdirectory(src)
endif()

if(BUILD_PLUGINS OR BUILD_PLUGINS_ONLY)
    message(STATUS "Build plugins are enable.")
    add_subdirectory(plugins)
else()
    message(WARNING "Build plugins are disable.")
endif()
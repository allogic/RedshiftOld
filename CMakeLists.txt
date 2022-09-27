cmake_minimum_required(VERSION 3.8)

project(Redshift VERSION 0.0.1 LANGUAGES C CXX)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binary/")
set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Assets/")
set(LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Library/")

add_subdirectory(Redshift)
add_subdirectory(Editor)
add_subdirectory(Sandbox)
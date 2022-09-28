cmake_minimum_required(VERSION 3.8)

project(Redshift VERSION 0.0.1 LANGUAGES C CXX)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binary/")
set(SCENE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Scenes/")
set(SCENE_STREAMING_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ScenesStreaming/")
set(LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Library/")

set(STATIC_LIBRARY_EXT ".a")
set(SHARED_LIBRARY_EXT ".so")

add_subdirectory(Redshift)
add_subdirectory(Editor)
add_subdirectory(Sandbox)
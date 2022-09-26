cmake_minimum_required(VERSION 3.8)

project(Redshift VERSION 0.0.1 LANGUAGES CXX)

set(BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Binary)
set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Shader)

add_subdirectory(Redshift)
add_subdirectory(Engine)
add_subdirectory(Sandbox)
cmake_minimum_required(VERSION 3.8)

project(Redshift VERSION 0.0.1 LANGUAGES C CXX)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binary")
set(VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Vendor")
set(LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Library")

set(MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Module")
set(MODULE_STREAMING_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ModuleStreaming")

set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Shader")
set(SHADER_STREAMING_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ShaderStreaming")

set(SHADER_EXT ".glsl")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  set(STATIC_LIBRARY_EXT ".lib")
  set(SHARED_LIBRARY_EXT ".dll")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(STATIC_LIBRARY_EXT ".a")
  set(SHARED_LIBRARY_EXT ".so")
endif()

add_subdirectory(Redshift)
add_subdirectory(Editor)
add_subdirectory(Sandbox)
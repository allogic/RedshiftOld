cmake_minimum_required(VERSION 3.8)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

set(TARGET_NAME Runtime)

file(GLOB_RECURSE GLAD_SOURCE ${VENDOR_DIR}/Glad/*.c ${VENDOR_DIR}/Glad/*.cpp)
file(GLOB_RECURSE IMGUI_SOURCE ${VENDOR_DIR}/ImGui/*.c ${VENDOR_DIR}/ImGui/*.cpp)
file(GLOB_RECURSE TARGET_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/*.c ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${TARGET_NAME}
  ${GLAD_SOURCE}
  ${IMGUI_SOURCE}
  ${TARGET_SOURCE}
)

set_target_properties(${TARGET_NAME} PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${BINARY_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR}
  PREFIX ""
  C_STANDARD 11
  CXX_STANDARD 20
)

target_include_directories(${TARGET_NAME}
  PUBLIC ${ROOT_DIR}
)

target_link_libraries(${TARGET_NAME}
  PUBLIC $<$<PLATFORM_ID:Linux>:stdc++fs>
  PUBLIC $<$<PLATFORM_ID:Linux>:pthread>
  PUBLIC ${OPENGL_LIBRARIES}
  PUBLIC ${CMAKE_DL_LIBS}
  PUBLIC ${BINARY_DIR}/Redshift${STATIC_LIBRARY_EXT}
  PUBLIC ${LIBRARY_DIR}/${CMAKE_SYSTEM_NAME}/glfw3${STATIC_LIBRARY_EXT}
)

target_compile_definitions(${TARGET_NAME}
  PUBLIC MODULE_DIR="${BINARY_DIR}"
  PUBLIC MODULE_EXT="${SHARED_LIBRARY_EXT}"
  PUBLIC MODULE_STREAMING_DIR="${MODULE_STREAMING_DIR}"
  PUBLIC SHADER_DIR="${SHADER_DIR}"
  PUBLIC SHADER_EXT="${SHADER_EXT}"
  PUBLIC SHADER_STREAMING_DIR="${SHADER_STREAMING_DIR}"
)

#target_compile_options(${TARGET_NAME}
#  PUBLIC $<$<CONFIG:Debug>:-O0 -g>
#  PUBLIC $<$<CONFIG:Release>:-Ofast>
#)
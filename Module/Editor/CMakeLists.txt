cmake_minimum_required(VERSION 3.8)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

set(TARGET_NAME Editor)

file(GLOB_RECURSE SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${VENDOR_DIR}/ImGui/imgui.cpp ${VENDOR_DIR}/ImGui/imgui_draw.cpp ${VENDOR_DIR}/ImGui/imgui_tables.cpp ${VENDOR_DIR}/ImGui/imgui_widgets.cpp
  ${VENDOR_DIR}/Glad/glad.c
)

add_library(${TARGET_NAME} SHARED
  ${SOURCE}
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
  PUBLIC ${OPENGL_LIBRARIES}
  PUBLIC ${BINARY_DIR}/Redshift${STATIC_LIBRARY_EXT}
  PUBLIC ${LIBRARY_DIR}/${CMAKE_SYSTEM_NAME}/glfw3${STATIC_LIBRARY_EXT}
)
cmake_minimum_required(VERSION 3.11...3.20)
project(sandbox)

file(GLOB_RECURSE src_file 
    "${PROJECT_SOURCE_DIR}/*/*.h"
    "${PROJECT_SOURCE_DIR}/*/*.hpp"
    "${PROJECT_SOURCE_DIR}/*/*.c"
    "${PROJECT_SOURCE_DIR}/*/*.cpp"
)

set(PIPELINE_BACKEND gl)
file(GLOB_RECURSE pipeline_file
    "${PROJECT_SOURCE_DIR}/pipeline/core/*.h"
    "${PROJECT_SOURCE_DIR}/pipeline/core/*.hpp"
    "${PROJECT_SOURCE_DIR}/pipeline/${PIPELINE_BACKEND}/*.c"
    "${PROJECT_SOURCE_DIR}/pipeline/${PIPELINE_BACKEND}/*.cpp"
)

add_executable(${PROJECT_NAME} 
    ${src_file}
    ${pipeline_file}
)

add_custom_target(
    CopySandBoxAssets
    COMMAND ${CMAKE_COMMAND} -E copy_directory  ${CMAKE_SOURCE_DIR}/assets ${BIN_DIR}/assets
    COMMENT "Copying asset to ${BIN_DIR}"
)

add_dependencies(${PROJECT_NAME} CopySandBoxAssets)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/pipeline
)

cmrc_add_resource_library(
    glsl-shader
    ALIAS glsl::shader
    NAMESPACE glsl
    shader/fragment_shader.fs
    shader/vertex_shader.vs
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        ${OPENGL_LIBRARIES}
        glew_s
        glfw
        glm
        stb_image
        spdlog::spdlog
        tl::expected
    PRIVATE
        glsl::shader
)

# setting up compile flags
set_property(TARGET ${PROJECT_NAME} APPEND_STRING
    PROPERTY COMPILE_FLAGS ${PROJECT_COMPILE_FLAG}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${BIN_DIR}/static_lib"
        ARCHIVE_OUTPUT_DIRECTORY "${BIN_DIR}/"
        RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}/"
)
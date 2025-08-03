cmake_minimum_required(VERSION 3.11...3.20)
project(pipeline)

set(BACKEND gl)

# source code dir
file(GLOB SRC 
    "${PROJECT_SOURCE_DIR}/core/*.h"
    "${PROJECT_SOURCE_DIR}/core/*.hpp"
    "${PROJECT_SOURCE_DIR}/core/*.c"
    "${PROJECT_SOURCE_DIR}/core/*.cpp"

    "${PROJECT_SOURCE_DIR}/${BACKEND}/*.h"
    "${PROJECT_SOURCE_DIR}/${BACKEND}/*.hpp"
    "${PROJECT_SOURCE_DIR}/${BACKEND}/*.c"
    "${PROJECT_SOURCE_DIR}/${BACKEND}/*.cpp"
)

add_library(${PROJECT_NAME} STATIC
    ${SRC} 
)
# setting up compile flags
set_property(TARGET ${PROJECT_NAME} APPEND_STRING
    PROPERTY COMPILE_FLAGS ${PROJECT_COMPILE_FLAG}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${BIN_DIR}"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}"
)

# setting up include dir
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    spdlog::spdlog
    tl::expected
    glew_s
    util
)

add_dependencies(${PROJECT_NAME}
    util
    glew_s
    spdlog::spdlog
)
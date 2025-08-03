cmake_minimum_required(VERSION 3.11...3.20)
project(window_backend)

set(BACKEND glfw)

# source code dir
file(GLOB SRC 
    "${PROJECT_SOURCE_DIR}/${BACKEND}_backend/*.h"
    "${PROJECT_SOURCE_DIR}/${BACKEND}_backend/*.hpp"
    "${PROJECT_SOURCE_DIR}/${BACKEND}_backend/*.cpp"
    "${PROJECT_SOURCE_DIR}/${BACKEND}_backend/*.c")

add_library(${PROJECT_NAME} STATIC
    ${SRC}
)
# setting up compile flags
set_property(TARGET ${PROJECT_NAME} APPEND_STRING
    PROPERTY COMPILE_FLAGS ${PROJECT_COMPILE_FLAG}
)

# setting up include dir
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    spdlog::spdlog
    glfw
    glew_s
    util
)

add_dependencies(${PROJECT_NAME}
    glfw
    glew_s
    spdlog::spdlog
)
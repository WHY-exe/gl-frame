cmake_minimum_required(VERSION 3.11...3.20)
project(gl_backend)

# source code dir
file(GLOB include_file "${PROJECT_SOURCE_DIR}/*.h")
aux_source_directory(${PROJECT_SOURCE_DIR} src)
add_library(${PROJECT_NAME} STATIC
    ${src} 
    ${include_file}
)
# setting up compile flags
set_property(TARGET ${PROJECT_NAME} APPEND_STRING
    PROPERTY COMPILE_FLAGS ${PROJECT_COMPILE_FLAG}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${BIN_DIR}/static_lib"
        ARCHIVE_OUTPUT_DIRECTORY "${BIN_DIR}/static_lib"
        RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}/static_lib"
)

# setting up include dir
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/..
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    pipeline_core
    util
)

add_dependencies(${PROJECT_NAME}
    pipeline_core
    util
)
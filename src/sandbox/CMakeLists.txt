# 这个项目输出可执行文件
project(sandbox)
# 让ide识别头文件
file(GLOB include_file 
        "${PROJECT_SOURCE_DIR}/src/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.hpp")

aux_source_directory(${PROJECT_SOURCE_DIR}/src main)
add_executable(${PROJECT_NAME} ${main} ${include_file})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    util
    ${OPENGL_LIBRARIES}
    glm
    spdlog::spdlog
    window_backend
    pipeline
    PRIVATE
    glsl::shader
)

add_dependencies(${PROJECT_NAME} 
    util 
    spdlog::spdlog 
    glm::glm
    window_backend
    pipeline
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
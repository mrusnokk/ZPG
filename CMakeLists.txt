cmake_minimum_required(VERSION 3.16)
project(zpg CXX)
set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/cviceni2/src/*.cpp)
add_executable(zpg ${SOURCES})

target_include_directories(zpg PRIVATE
    cviceni2/src
    cviceni2
    lib
    lib/glm-master)

target_link_libraries(zpg PRIVATE glfw OpenGL::GL)

# Kopírování shaderů a textur vedle spustitelného souboru
add_custom_command(TARGET zpg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/cviceni2/Shaders $<TARGET_FILE_DIR:zpg>/Shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/cviceni2/Shaders $<TARGET_FILE_DIR:zpg>/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/cviceni2/src/textures $<TARGET_FILE_DIR:zpg>/src/textures)

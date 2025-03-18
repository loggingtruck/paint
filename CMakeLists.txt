cmake_minimum_required(VERSION 3.10)
project(paint LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Find GLFW package
set(glfw3_DIR ${CMAKE_SOURCE_DIR}/libraries/glfw/lib/cmake/glfw3)
find_package(glfw3 REQUIRED)

# Find GLAD
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/libraries/glad)
add_library(glad STATIC ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)

# Define source files and headers
set(SOURCES
    src/App.c
    src/Canvas.c
    src/InputHandler.c
    src/Main.c
    src/Shader.c
    src/Renderer.c
)

set(HEADERS
    header/App.h
    header/Canvas.h
    header/InputHandler.h
    header/Main.h
    header/Shader.h
    header/Renderer.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/libraries/glad/include  # List glad include first
    ${CMAKE_SOURCE_DIR}/libraries/glfw/include
    ${CMAKE_SOURCE_DIR}/header
    ${CMAKE_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glad    # List glad first
    glfw
    OpenGL::GL
)
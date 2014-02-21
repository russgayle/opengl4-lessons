# Lesson 3

include_directories(${OpenGL4-Tutorial_SOURCE_DIR}/queso)

# build it, and they will come
add_executable(lesson3 main.cpp)
target_link_libraries(lesson3 queso)

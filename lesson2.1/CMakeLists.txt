# Lesson 2.1 - Make a queso friendly version of lesson 2.

include_directories(${OpenGL4-Tutorial_SOURCE_DIR}/queso)

# build it, and they will come
add_executable(lesson2 main.cpp)
target_link_libraries(lesson2 queso)

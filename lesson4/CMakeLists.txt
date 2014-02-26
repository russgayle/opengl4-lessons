# Lesson 2.1 - Make a queso friendly version of lesson 2.

include_directories(${OpenGL4-Tutorial_SOURCE_DIR}/queso)

# build it, and they will come
add_executable(lesson4 main.cpp)
target_link_libraries(lesson4 queso)

file(GLOB shaders "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.*")
install(FILES ${shaders} DESTINATION lesson4/shaders)

install(TARGETS lesson4
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

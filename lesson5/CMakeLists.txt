# Lesson 5: Practice with matrix / vector operations

include_directories(${OpenGL4-Tutorial_SOURCE_DIR}/queso)

# build it, and they will come
add_executable(lesson5 main.cpp)
target_link_libraries(lesson5 queso)

file(GLOB shaders "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.*")
install(FILES ${shaders} DESTINATION lesson4/shaders)

install(TARGETS lesson5
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

# Lesson 3

include_directories(${OpenGL4-Tutorial_SOURCE_DIR}/queso)

# build it, and they will come
add_executable(lesson3 main.cpp)
target_link_libraries(lesson3 queso)

file(GLOB shaders "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.*")
install(FILES ${shaders} DESTINATION lesson3/shaders)

install(TARGETS lesson3
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)


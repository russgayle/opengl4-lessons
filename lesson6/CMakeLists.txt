# Lesson 6: Virtual Camera

include_directories(${OpenGL4-Tutorial_SOURCE_DIR}/queso)
include_directories(${OpenGL4-Tutorial_SOURCE_DIR}/glm)

# build it, and they will come
add_executable(camera_toy main.cpp)
target_link_libraries(camera_toy queso)

install(TARGETS camera_toy 
  RUNTIME DESTINATION ${CMAKE_BINARY_DIR}
  LIBRARY DESTINATION ${CMAKE_BINARY_DIR}
  ARCHIVE DESTINATION ${CMAKE_BINARY_DIR} 
)

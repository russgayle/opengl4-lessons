# Phong lighting (per pixel!)

include_directories(${OpenGL4-Tutorial_SOURCE_DIR}/queso)
include_directories(${OpenGL4-Tutorial_SOURCE_DIR}/glm)

# build it, and they will come
add_executable(phong_toy main.cpp)
target_link_libraries(phong_toy queso)

install(TARGETS phong_toy 
  RUNTIME DESTINATION ${CMAKE_BINARY_DIR}
  LIBRARY DESTINATION ${CMAKE_BINARY_DIR}
  ARCHIVE DESTINATION ${CMAKE_BINARY_DIR} 
)

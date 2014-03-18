#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

out vec3 position_eye;
out vec3 normal_eye;
out vec3 color;

void main() {
  color = vertex_color;
  position_eye = vec3(view * model * vec4(vertex_position, 1.0));
  normal_eye = vec3(view * model * vec4(vertex_normal, 0.0));
  gl_Position = proj * view * vec4(vertex_position, 1.0);
}


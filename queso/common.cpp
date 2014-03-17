#include "common.h"

// Define queso's "globals"
namespace queso {
  bool paused = true;

  float camPos[] = { 0.0f, 0.0f, 2.0f };
  float camYaw = 0.0f;
  float camSpeed = 0.05f;
  float camRotSpeed = 3.1415192 / 90.0;

  float lightPos[] = { 10.0f, 10.0f, 10.0f };
  float specularColor[] = { 1.0f, 1.0f, 1.0f };
  float diffuseColor[] = { 0.7f, 0.7f, 0.7f };
  float ambientColor[] = { 0.2f, 0.2f, 0.2f };
}

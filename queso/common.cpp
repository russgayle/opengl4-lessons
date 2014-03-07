#include "common.h"

// Define queso's "globals"
namespace queso {
  bool paused = true;

  float camPos[] = { 0.0f, 0.0f, 2.0f };
  float camYaw = 0.0f;
  float camSpeed = 1.0f;
  float camRotSpeed = 3.1415192 / 18.0;
}

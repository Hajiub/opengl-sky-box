#ifndef UTILS_H
#define UTILS_H

#include "../header.h"

namespace Utils {
  std::string readFileToString(const char *);
  unsigned long currentTimeMillis();
  float randFloat(float min, float max);
  unsigned int loadTexture(const char *path, bool gamma = false);
  unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
}

#endif // UTILS_h
#pragma once

#include <string>

namespace protocol {
  std::string scale(const double depth, const double breadth);
  std::string setPhysics(void);
  std::string iterate(const unsigned int count);
  std::string renderSvg(void);
  std::string stop(void);
}

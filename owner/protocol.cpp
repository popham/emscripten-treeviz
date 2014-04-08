#include "protocol.hpp"

#include <worker/command.hpp>
#include "json.hpp"

namespace protocol {
  std::string scale(const double depth, const double breadth) {
    return json::open()
      + json::pair("command", command::SCALE) + ","
      + json::pair("depth", std::to_string(depth)) + ","
      + json::pair("breadth", std::to_string(breadth))
      + json::close();
  }

  std::string setPhysics(void) {
    return json::open()
      + json::pair("command", command::SET_PHYSICS)
      + json::close();
  }

  std::string iterate(const unsigned int count) {
    return json::open()
      + json::pair("command", command::ITERATE) + ","
      + json::pair("count", std::to_string(count))
      + json::close();
  }

  std::string renderSvg(void) {
    return json::open()
      + json::pair("command", command::RENDER_SVG)
      + json::close();
  }

  std::string stop(void) {
    return json::open()
      + json::pair("command", command::STOP)
      + json::close();
  }
}

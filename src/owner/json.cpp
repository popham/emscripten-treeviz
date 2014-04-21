#include "json.hpp"

namespace json {
  std::string open(void) {
    return "{";
  }

  std::string close(void) {
    return "}";
  }

  std::string pair(std::string const & string, std::string const & value) {
    std::string p = "\"";
    p += string;
    p += "\":";
    p += value;

    return p;
  }
}

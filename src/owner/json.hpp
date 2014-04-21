#pragma once

#include <string>

namespace json {
  std::string open(void);
  std::string close(void);

  std::string pair(std::string const & string, std::string const & value);
}

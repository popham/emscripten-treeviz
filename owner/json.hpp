#pragma once

#include <string>
#include <worker/command.hpp>

namespace json {
  std::string open(void);
  std::string close(void);

  std::string pair(std::string const & string, std::string const & value);
  std::string pair(std::string const & string, command::Command value);
}

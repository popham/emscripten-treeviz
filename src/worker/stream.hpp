#pragma once

#include <string>
#include <ostream>

#include <boost/format.hpp>

template <typename T>
std::string to_string(T const &);

template <>
std::string to_string(boost::format const &);

class UnescapedJson {
public:
  UnescapedJson(void);
  UnescapedJson(char const * const s);
  UnescapedJson(std::string const & s);
  template <typename T> UnescapedJson(T const & data)
    : UnescapedJson(to_string(data)) {}

  char const * c_str(void) const;
  std::string::const_iterator begin(void) const;
  std::string::const_iterator end(void) const;

private:
  std::string _s;
};

std::ostream & operator<<(std::ostream & target, UnescapedJson const & source);

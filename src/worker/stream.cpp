#include "stream.hpp"

template <typename T>
std::string to_string(T const & data) {
  return std::to_string(data);
}

template <>
std::string to_string(boost::format const & data) {
  return data.str();
}

UnescapedJson::UnescapedJson(void) : _s("") {}
UnescapedJson::UnescapedJson(char const * const s) : _s(s) {}
UnescapedJson::UnescapedJson(std::string const & s) : _s(s) {}
char const * UnescapedJson::c_str(void) const { return _s.c_str(); }
std::string::const_iterator UnescapedJson::begin(void) const { return _s.cbegin(); }
std::string::const_iterator UnescapedJson::end(void) const { return _s.cend(); }

// Lifted from stack exchange (converted to streaming implementation).
std::ostream & operator<<(std::ostream & os, UnescapedJson const & source) {
  for (const auto ci : source) {
    switch (ci) {
    case '\\': os << "\\\\"; break;
    case '"':  os << "\\\""; break;
    case '/':  os << "\\/";  break;
    case '\b': os << "\\b";  break;
    case '\f': os << "\\f";  break;
    case '\n': os << "\\n";  break;
    case '\r': os << "\\r";  break;
    case '\t': os << "\\t";  break;
    default:   os << ci;     break;
    }
  }
  return os;
}

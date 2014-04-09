#include <worker/matching.hpp>

#include <string>

#include <lest/lest.hpp>

char const * const r[] = {
  static_cast<char const * const>("a"),
  static_cast<char const * const>("b"),
  static_cast<char const * const>("c"),
  static_cast<char const * const>("d"),
  static_cast<char const * const>("e")
};

char const * const s[] = {
  static_cast<char const * const>("x"),
  static_cast<char const * const>("y"),
  static_cast<char const * const>("z")
};

const lest::test stack[] =
{
  "Short", []
  {

  },

  "", []
  {

  }
};

int main(void) {
  return lest::run(stack);
}

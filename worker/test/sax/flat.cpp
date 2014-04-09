#include <worker/test/sax.hpp>

#include <worker/layout.hpp>
#include <owner/json.hpp>

char const * const vPathRaw[] = {
  static_cast<char const * const>("id")
};

char const * const eBaseRaw[] = {
  static_cast<char const * const>("parents")
};
char const * const ePathRaw[] = {};

const Path vertexPath(&vPathRaw[0], 1);
const Path parentsBase(&eBaseRaw[0], 1);
const Path parentsPath(&ePathRaw[0], 0);

const std::string jsonMock = "[" +
  json::open() +
    json::pair("id", "1") +
    "," +
    json::pair("parents", "[2,3]") +
  json::close() +
  "," +
  json::open() +
    json::pair("id", "2") +
    "," +
    json::pair("parents", "[3]") +
  json::close() +
  "," +
  json::open() +
    json::pair("id", "3") +
  // Parents excluded intentionally to check robustness.
  json::close() +
"]";

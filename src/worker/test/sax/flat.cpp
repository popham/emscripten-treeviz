#include <worker/test/sax.hpp>

#include <owner/json.hpp>

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

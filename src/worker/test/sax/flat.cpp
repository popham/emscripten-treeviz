#include <worker/test/sax.hpp>

const std::string jsonMock = std::string("[")
  + R"({"id":1, "parents":[2,3]})"
  + ","
  + R"({"id":2, "parents":[3]})"
  + ","
  + R"({"id":3})"
  + "]";

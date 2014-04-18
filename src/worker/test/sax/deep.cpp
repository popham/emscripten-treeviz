#include <worker/test/sax.hpp>

const std::string jsonMock = std::string("[")

  + R"({"layer1":{"layer2":{"id":1}, "mayer2":[]}, "junk1":{"junk2":5}})"

  + ","

  + R"({"layer1":{"layer2":{"id":2}, "mayer2":[)"
  +   R"({"mayer3":{"parentId":1, "junk":""}})"
  + R"(]}})"

  + ","

  + R"({"layer1":{"layer2":{"id":3}, "mayer2":[)"
  +   R"({"mayer3":{"parentId":2,"other":7}}, {"mayer3":{"junk":3,"parentId":1}})"
  + R"(]}})"

  + "]";

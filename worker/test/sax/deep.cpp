#include <worker/test/sax.hpp>

#include <worker/layout.hpp>
#include <owner/json.hpp>

char const * const vPathRaw[] = {
  static_cast<char const * const>("layer1"),
  static_cast<char const * const>("layer2"),
  static_cast<char const * const>("id")
};

char const * const eBaseRaw[] = {
  static_cast<char const * const>("layer1"),
  static_cast<char const * const>("mayer2")
};
char const * const ePathRaw[] = {
  static_cast<char const * const>("mayer3"),
  static_cast<char const * const>("parentId")
};

const Path vertexPath(&vPathRaw[0], 3);
const Path parentsBase(&eBaseRaw[0], 2);
const Path parentsPath(&ePathRaw[0], 2);

const std::string jsonMock = "[" +
  json::open() +
    json::pair("layer1",
      json::open() +
        json::pair("layer2",
          json::open() + json::pair("id", "1") + json::close()
        ) +
        "," +
        json::pair("mayer2", "[]") +
      json::close()
    ) +
  json::close() +
  "," +
  json::open() +
    json::pair("layer1",
      json::open() +
        json::pair("layer2",
          json::open() +
            json::pair("id", "2") +
          json::close()
        ) +
        "," +
        json::pair("mayer2",
          "[" +
            json::open() +
              json::pair("mayer3",
                json::open() +
                  json::pair("parentId", "3") +
                json::close()
              ) +
            json::close() +
          "]"
        ) +
      json::close()
    ) +
  json::close() +
  "," +
  json::open() +
    json::pair("layer1",
      json::open() +
        json::pair("layer2",
          json::open() +
            json::pair("id", "1") +
          json::close()
        ) +
        "," +
        json::pair("mayer2",
          "[" +
            json::open() +
              json::pair("mayer3",
                json::open() +
                  json::pair("parentId", "2") +
                json::close()
              ) +
            json::close() +
            "," +
            json::open() +
              json::pair("mayer3",
                json::open() +
                  json::pair("parentId", "3") +
                json::close()
              ) +
            json::close() +
          "]"
        ) +
      json::close()
    ) +
  json::close() +
"]";

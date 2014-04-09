#include <worker/test/sax.hpp>

#include <owner/json.hpp>

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

#include <string>

#include <worker/builder.hpp>
#include <lest/lest.hpp>
#include <owner/json.hpp>

const std::string first_empty_mock = "["
  + json::open() + json::pair("id", "1") + json::close() + ","
  + json::open() + json::pair("id", "2") + json::close()
  + "]";

// 
const lest::test first_empty = {};

const std::string second_empty_mock = "["
  + json::open() + json::pair("layer1",
      json::open() + json::pair("layer2", "[5, 6, 7]") + json::close()
    )
  + json::close() +"]";

const lest::test second_empty = {};

const std::string both_empty_mock = "[[1,2,3]]";

const lest::test both_empty = {}

#include "sax.hpp"

#include <sstream>

#include <boost/format.hpp>
#include <lest/lest.hpp>

#include <worker/accept.hpp>

#include <worker/request.hpp>
#include <worker/response.hpp>

// Do nothing on get (use the `inject` method on the global tree instead).
extern "C" void get(bound_buffer * target, char const * const) {}

// buffer responses for tests to validate against
std::stringstream responses;

extern "C" void emscripten_worker_respond(char const * const data, unsigned int length) {
  responses << std::string(data, length);
}

extern "C" void emscripten_worker_respond_provisionally(char const * const data, unsigned int length) {
  responses << std::string(data, length);
}

std::string dump_responses(void) {
  std::string r = responses.str();
  responses.str("");
  return r;
}

const lest::test walk[] = 
{
  "Parse mock data without flagging an error", []
  {
    treeish.clear();
    treeish.inject(jsonMock.c_str());
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == sought.str() );
  },

  "Constructed graph contains 3 vertices", []
  {
    EXPECT( treeish.nVertices() == 3 );
  },

  "Constructed graph contains 3 edges", []
  {
    EXPECT( treeish.nEdges() == 3 );
  }
};

int main(void)
{
    return lest::run(walk);
}

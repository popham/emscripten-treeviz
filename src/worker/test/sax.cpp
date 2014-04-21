#include "sax.hpp"

#include <sstream>

#include <boost/format.hpp>
#include <lest/lest.hpp>

#include <worker/command.hpp>
#include <worker/graph.hpp>
#include <worker/request.hpp>
#include <worker/response.hpp>

Graph theGraph;

// Do nothing on get (use the `inject` method on the global tree instead).
extern "C" void getJson(bound_buffer * target, char const * const) {}

// buffer responses for tests to validate against
std::stringstream responses;

extern "C" void emscripten_worker_respond(char const * const data, int length) {
  responses << std::string(data, length);
}

extern "C" void emscripten_worker_respond_provisionally(char const * const data, int length) {
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
    inject(jsonMock.c_str());
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == sought.str() );
  },

  "Construct graph with 3 vertices", []
  {
    EXPECT( boost::num_vertices(theGraph) == 3 );
  },

  "Construct graph with 3 edges", []
  {
    EXPECT( boost::num_edges(theGraph) == 3 );
  }
};

int main(void) {
  std::cout << jsonMock.c_str() << std::endl;
  return lest::run(walk);
}

#include <string>
#include <sstream>

#include <rapidxml/rapidxml.hpp>
#include <rapidjson/document.h>
#include <boost/format.hpp>
#include <lest/lest.hpp>

#include <owner/json.hpp>
#include <worker/command.hpp>
#include <worker/graph.hpp>
#include <worker/request.hpp>
#include <worker/response.hpp>

Graph theGraph;

// Do nothing on get (use the `inject` method on the global tree instead).
extern "C" void getJson(bound_buffer * target, char const * const) {}

// Clobber head up to and including the first ':'.
std::string & trim(std::string & s) {
  s = s.substr(s.find(':')+1);
  return s;
}

std::string final(std::string data) {
  return "Finalizing Response: " + data;
}

std::string final(boost::format const & data) {
  return final(data.str());
}

std::string provisional(std::string data) {
  return "Provisional Response: " + data;
}

std::string provisional(boost::format const & data) {
  return provisional(data.str());
}

// buffer responses for tests to validate against
std::stringstream responses;

extern "C" void emscripten_worker_respond(char const * const data, int length) {
  responses << final(std::string(data, length));
}

extern "C" void emscripten_worker_respond_provisionally(char const * const data, int length) {
  responses << provisional(std::string(data, length));
}

// Mock data
const std::string dag = "["
  + json::open() + json::pair("id", "1") + json::close() + ","
  + json::open() + json::pair("id", "2") + "," + json::pair("parents", "[1]") + json::close() + ","
  + json::open() + json::pair("id", "3") + "," + json::pair("parents", "[1]") + json::close() + ","
  + json::open() + json::pair("id", "4") + "," + json::pair("parents", "[1]") + json::close() + ","
  + json::open() + json::pair("id", "5") + "," + json::pair("parents", "[2,3]") + json::close() + ","
  + json::open() + json::pair("id", "6") + "," + json::pair("parents", "[3,4]") + json::close() + ","
  + json::open() + json::pair("id", "7") + "," + json::pair("parents", "[5,6]") + json::close()
  + "]";

char const * const vPathRaw[] = {static_cast<char const * const>("id")};
char const * const ePathRaw[] = {static_cast<char const * const>("parents")};
const Path theVertexPath(&vPathRaw[0], 1);
const Path theParentsBase(&ePathRaw[0], 1);
const Path theParentsPath(0, 0);

std::string dump_responses(void) {
  std::string r = responses.str();
  responses.str("");
  return r;
}

const lest::test interrogate[] =
{
  "Inject method parses mock data and responds Void", []
  {
    inject(dag.c_str());
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  },

  "Inject method maps mock data to its expected topology", []
  {
    // Vertices
    EXPECT( contains(0) );
    EXPECT( contains(1) );
    EXPECT( contains(2) );
    EXPECT( contains(3) );
    EXPECT( contains(4) );
    EXPECT( contains(5) );
    EXPECT( contains(6) );

    // Edges
    EXPECT( contains(0,1) );
    EXPECT( contains(0,2) );
    EXPECT( contains(0,3) );
    EXPECT( contains(1,4) );
    EXPECT( contains(2,4) );
    EXPECT( contains(2,5) );
    EXPECT( contains(3,5) );
    EXPECT( contains(4,6) );
    EXPECT( contains(5,6) );
  },

  "Scale method responds Void", []
  {
    scale(5,10);
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  },

  "Set Physics method responds Void", []
  {
    setPhysics();
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  },

  "Iterate method responds Void", []
  {
    iterate(7);
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  },

  "Render SVG method generates an XML fragment and responds SVG", []
  {
    renderSvg(1);

    rapidjson::Document svgResponse;
    std::string raw = dump_responses();
    EXPECT( !svgResponse.Parse<rapidjson::kParseDefaultFlags>(trim(raw).c_str()).HasParseError() );
    EXPECT( svgResponse["response"].GetUint() == response::SVG );

    rapidxml::xml_document<> svg;
    char * fragment = const_cast<char *>(svgResponse["fragment"].GetString());
    // Bind a return value to rapidxml's parsing for Lest (checking no throw).
    EXPECT( [&]{ svg.parse<rapidxml::parse_fastest>(fragment); return true; }() );
  },

  "Scale method responds Void", []
  {
    scale(10,15);
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  },

  "Stop method responds Clean", []
  {
    stop();
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::CLEAN);
    EXPECT( dump_responses() == final(sought) );
  },

  "Scale method responds Void", []
  {
    scale(10,15);
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  }
};

int main(void)
{
    return lest::run(interrogate);
}

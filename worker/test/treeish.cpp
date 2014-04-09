#include <string>
#include <sstream>

#include <rapidxml/rapidxml.hpp>
#include <rapidjson/document.h>
#include <boost/format.hpp>
#include <lest/lest.hpp>

#include <owner/json.hpp>
#include <owner/protocol.hpp>
#include <worker/accept.hpp>
#include <worker/layout.hpp>
#include <worker/request.hpp>
#include <worker/response.hpp>

//char const * const vBaseRaw[] = {};
char const * const vPathRaw[] = {static_cast<char const * const>("id")};
//char const * const eBaseRaw[] = {};
char const * const ePathRaw[] = {static_cast<char const * const>("parents")};
const Path vertexBase(0, 0);
const Path vertexPath(&vPathRaw[0], 1);
const Path parentsBase(0, 0);
const Path parentsPath(&ePathRaw[0], 1);

void trigger(std::string const & data) {
  accept(data.c_str(), data.length());
}

// Do nothing on get (use the `inject` method on the global tree instead).
extern "C" void get(bound_buffer * target, char const * const) {}

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

extern "C" void emscripten_worker_respond(char const * const data, unsigned int length) {
  responses << final(std::string(data, length));
}

extern "C" void emscripten_worker_respond_provisionally(char const * const data, unsigned int length) {
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

std::string dump_responses(void) {
  std::string r = responses.str();
  responses.str("");
  return r;
}

const lest::test interrogate[] =
{
  "Treeish parses mock data and responds Void", []
  {
    treeish.clear(); // Take global to default constructed initial state.
    treeish.inject(dag.c_str());
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  },

  "Treeish parses a Scale command and responds Void", []
  {
    trigger(protocol::scale(5,10));
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  },

  "Treeish parses a Set Physics command and responds Void", []
  {
    trigger(protocol::setPhysics());
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  },

  "Treeish parses an Iterate command and responds Void", []
  {
    trigger(protocol::iterate(7));
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  },

  "Treeish parses a Render SVG command and responds SVG", []
  {
    trigger(protocol::renderSvg());

    rapidjson::Document svgResponse;
    std::string raw = dump_responses();
    EXPECT( !svgResponse.Parse<rapidjson::kParseDefaultFlags>(trim(raw).c_str()).HasParseError() );
    EXPECT( svgResponse["response"].GetUint() == response::SVG );

    rapidxml::xml_document<> svg;
    char * fragment = const_cast<char *>(svgResponse["fragment"].GetString());
    // Bind a return value to rapidxml's parsing for Lest (checking no throw).
    EXPECT( [&]{ svg.parse<rapidxml::parse_fastest>(fragment); return true; }() );
  },

  "Treeish parses another Scale command and responds Void", []
  {
    trigger(protocol::scale(10,15));
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  },

  "Treeish parses a Stop command and responds Clean", []
  {
    trigger(protocol::stop());
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::CLEAN);
    EXPECT( dump_responses() == final(sought) );
  },

  "Treeish parses a Scale command and errors out", []
  {
    trigger(protocol::scale(10,15));
    boost::format sought = boost::format(R"({"response":%s})")
      % std::to_string(response::VOID);
    EXPECT( dump_responses() == provisional(sought) );
  }
};

int main(void)
{
    return lest::run(interrogate);
}

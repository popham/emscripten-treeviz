#include "response.hpp"

#include <string>
#include <sstream>

#include "stream.hpp"

namespace response {

  static const std::string VOID_RESPONSE =
    R"({"response":)" + std::to_string((int)Response::VOID) + "}";

  static const std::string CLEAN_RESPONSE =
    R"({"response":)" + std::to_string((int)Response::CLEAN) + "}";

  void respond(const Response response,
               char const * const message_key,
               char const * const message) {
    std::stringstream r;
    r << "{\"response\":"
      << (int)response
      << ",\""
      << UnescapedJson(message_key)
      << "\":\""
      << UnescapedJson(message)
      << "\"}";

    emscripten_worker_respond_provisionally(r.str().c_str(), r.str().length());
  }

  void nullary(char const * const key, char const * const value) {
    std::stringstream n;
    n << "{\""
      << UnescapedJson(key)
      << "\":\""
      << UnescapedJson(value)
      << "\"}";

    emscripten_worker_respond_provisionally(n.str().c_str(), n.str().length());
  }

  void log(char const * const message) {
    nullary("log", message);
  }

  void error(char const * const message) {
    nullary("error", message);
  }

  void incompleteBindingError(char const * const attempted_command) {
    std::string e = "'";
    e += attempted_command;
    e += "' was called without all of its parameters bound.  Are you sure that you sent them?";

    error(e.c_str());
  }

  void vacuous(void) {
    emscripten_worker_respond_provisionally(VOID_RESPONSE.c_str(),
                                            VOID_RESPONSE.length());
  }

  void clean(void) {
    emscripten_worker_respond(CLEAN_RESPONSE.c_str(),
                              CLEAN_RESPONSE.length());
  }
}

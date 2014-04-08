#include "response.hpp"

#include <string>

namespace response {

  static const std::string VOID_RESPONSE =
    "{\"response\":" + std::to_string((int)Response::VOID) + "}";

  static const std::string CLEAN_RESPONSE =
    "{\"response\":" + std::to_string((int)Response::CLEAN) + "}";

  void respond(const Response response,
               char const * const message_key,
               char const * const message) {
    std::string r = "{\"response\":";
    r += std::to_string((int)response);
    r += ",\"";
    r += message_key;
    r += "\":\"";
    r += message;
    r += "\"}";

    emscripten_worker_respond_provisionally(r.c_str(), r.length());
  }

  void error(char const * const message) {
    std::string e = "{\"error\":\"";
    e += message;
    e += "\"}";

    emscripten_worker_respond_provisionally(e.c_str(), e.length());
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

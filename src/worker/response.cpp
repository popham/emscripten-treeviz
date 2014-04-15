#include "response.hpp"

#include <string>

namespace response {

  static const std::string VOID_RESPONSE =
    R"({"response":)" + std::to_string((int)Response::VOID) + "}";

  static const std::string CLEAN_RESPONSE =
    R"({"response":)" + std::to_string((int)Response::CLEAN) + "}";

  void respond(const Response response,
               char const * const message_key,
               char const * const message) {
    std::string r = R"({"response":)";
    r += std::to_string((int)response);
    r += R"(,")";
    r += message_key;
    r += R"(":")";
    r += message;
    r += R"("})";

    emscripten_worker_respond_provisionally(r.c_str(), r.length());
  }

  void error(char const * const message) {
    std::string e = R"({"error":")";
    e += message;
    e += R"("})";

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
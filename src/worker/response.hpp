#pragma once

extern "C" {
  extern void emscripten_worker_respond(char const * const, int);
  extern void emscripten_worker_respond_provisionally(char const * const, int);
}

namespace response {

  enum Response {
    VOID   = 1,
    CLEAN  = 2,
    SVG    = 20,
  };

  typedef enum Response Response;

  void respond(const Response response,
               char const * const message_key,
               char const * const message);
  void error(char const * const message);
  void incompleteBindingError(char const * const attempted_command);
  void vacuous(void);
  void clean(void);
}

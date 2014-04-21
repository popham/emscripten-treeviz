#include "command.hpp"

void load(char const * const url) {
  bound_buffer bb;
  getJson(&bb, url);
  /*
  if (failed) {
    response::errorish(std::string(bb.first, bb.length));
    free(bb.first);
  }
  */
  response::log("Loaded JSON data");
  inject(bb.first);
  dealloc_bound_buffer(&bb);
}

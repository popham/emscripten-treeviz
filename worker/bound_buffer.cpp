#include "bound_buffer.hpp"

#include <cstdlib>

extern "C" void init_bound_buffer(bound_buffer * target,
                                  char * first,
                                  unsigned int length) {
  target->first = first;
  target->length = length;
}

extern "C" unsigned int sizeof_bound_buffer(void) {
  return sizeof(bound_buffer);
}

void dealloc_bound_buffer(bound_buffer * p) {
  std::free(p->first);
}

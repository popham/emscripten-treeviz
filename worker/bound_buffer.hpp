#pragma once

// Returning null terminated string to avoid this complexity--hope it works.
// Delete me if ok
struct bound_buffer {
  char * first;
  unsigned int length;
};

extern "C" void init_bound_buffer(bound_buffer * target,
                                  char * first,
                                  int length);
extern "C" unsigned int sizeof_bound_buffer(void);
void dealloc_bound_buffer(bound_buffer * p);

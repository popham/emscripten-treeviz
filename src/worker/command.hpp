#pragma once

#include "graph.hpp"
#include "response.hpp"
#include "layout.hpp"

extern "C" void inject(char const * const);
extern "C" void load(char const * const url);
extern "C" void scale(const double depth, const double breadth);
extern "C" void setPhysics(void);
extern "C" void iterate(const unsigned int count);
extern "C" void renderSvg(unsigned int root);
extern "C" void stop(void);

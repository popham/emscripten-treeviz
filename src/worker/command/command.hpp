#pragma once

#include <worker/graph.hpp>
#include <worker/response.hpp>

extern "C" void inject(char const * const);
extern "C" void load(char const * const url);
extern "C" void scale(const double depth, const double breadth);
extern "C" void setPhysics(void);
extern "C" void iterate(const unsigned int count);
extern "C" void renderSvg(unsigned int root) const;
extern "C" void stop(void);

extern Graph theGraph;

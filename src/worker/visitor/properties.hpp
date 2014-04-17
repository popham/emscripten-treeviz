#pragma once

#include <list>
#include <iostream>
#include <boost/property_map/vector_property_map.hpp>

#include <worker/graph.hpp>

struct Slot {
  Slot(void) : depth(0), breadth(0) {}
  Slot(unsigned int b, unsigned int d) : breadth(b), depth(d) {}
  unsigned int breadth;
  unsigned int depth;
};

using Color = boost::default_color_type;
using Slots = std::list<Slot>;

bool operator==(Slot const & lhs, Slot const & rhs);
bool operator!=(Slot const & lhs, Slot const & rhs);
std::ostream & operator<<(std::ostream & os, Slot const & rhs);
std::ostream & operator<<(std::ostream & os, Slots const & rhs);

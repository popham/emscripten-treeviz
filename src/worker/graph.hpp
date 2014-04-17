#pragma once

#include <vector>
#include <list>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>

struct Position {
  Position(void) : depth(0), breadth(0) {}
  Position(unsigned int d, unsigned int b) : depth(d), breadth(b) {}
  unsigned int depth;
  unsigned int breadth;
};

using Positions = std::list<Position>;

bool operator==(Position const & lhs, Position const & rhs);
bool operator!=(Position const & lhs, Position const & rhs);

std::ostream & operator<<(std::ostream & os, Position const & rhs);
std::ostream & operator<<(std::ostream & os, Positions const & rhs);

struct VertexBlob {
  // First element must remain consistent with other positions in the graph.
  Positions positions;
};

using ColorMap = boost::vector_property_map<boost::default_color_type>;

using Graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::directedS,
  VertexBlob
  >;

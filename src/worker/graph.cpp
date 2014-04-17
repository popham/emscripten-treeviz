#include "graph.hpp"

bool operator==(Position const & lhs, Position const & rhs) {
  return lhs.breadth==rhs.breadth && lhs.depth==rhs.depth;
}

bool operator!=(Position const & lhs, Position const & rhs) {
  return !(lhs==rhs);
}

std::ostream & operator<<(std::ostream & os, Position const & rhs) {
  return os << "(" << rhs.breadth << "," << rhs.depth << ")";
}

std::ostream & operator<<(std::ostream & os, Positions const & rhs) {
  bool first = true;
  for (Position p : rhs) {
    if (!first) {
      os << ',';
      first = false;
    }

    os << p;
  }

  return os;
}

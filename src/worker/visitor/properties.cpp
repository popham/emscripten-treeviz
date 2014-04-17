#include "properties.hpp"

bool operator==(Slot const & lhs, Slot const & rhs) {
  return lhs.breadth==rhs.breadth && lhs.depth==rhs.depth;
}

bool operator!=(Slot const & lhs, Slot const & rhs) {
  return !(lhs==rhs);
}

std::ostream & operator<<(std::ostream & os, Slot const & rhs) {
  return os << "(" << rhs.breadth << "," << rhs.depth << ")";
}

std::ostream & operator<<(std::ostream & os, Slots const & rhs) {
  bool first = true;
  for (Slot s : rhs) {
    if (!first) {
      os << ',';
      first = false;
    }

    os << s;
  }

  return os;
}

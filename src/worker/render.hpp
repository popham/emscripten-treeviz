#include <sstream>

#include "graph.hpp"

namespace svg {

  extern void render(Graph const &,
                     typename Graph::vertex_descriptor root,
                     std::stringstream & ss);

}

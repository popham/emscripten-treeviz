#include <sstream>

#include <worker/graph.hpp>
#include <worker/render/hypothetical.hpp>

namespace svg {

  void render(Graph const & g,
              typename Graph::vertex_descriptor root,
              std::stringstream & ss) {
    svg::hypothetical(g, root, ss);
  }

}

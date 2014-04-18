#include <sstream>

#include <worker/graph.hpp>
#include <worker/render/hypothetical.hpp>

void renderSvg(Graph const & g,
               typename Graph::vertex_descriptor root,
               std::stringstream & ss) {
  render::hypothetical(g, root, ss);
}

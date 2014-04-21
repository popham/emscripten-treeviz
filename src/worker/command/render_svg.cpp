#include "command.hpp"

#include <sstream>

void renderSvg(unsigned int root) const {
  bool * pParentExists = new bool[boost::num_vertices(theGraph)];
  for (auto e : range_pair(boost::edges(theGraph))) {
    pParentExists[boost::target(e)] = true;
  }

  Graph::vertex_descriptor r;
  bool isFound = false;
  for (auto v : range_pair(boost::vertices(theGraph))) {
    if (!pParentExists[v]) {
      if (isFound) {
        response::error("More than one disconnected components have been found");
        return;
      } else {
        isFound = true;
        r = v;
      }
    }
  }

  if (!isFound) {
    response::error("No disconnected components were found");
    return;
  }

  std::stringstream ss;
  ::renderSvg(theGraph, r, ss);
  response::respond(response::SVG, "fragment", ss.str().c_str());
}

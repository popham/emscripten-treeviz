#include "../command.hpp"

#include <sstream>
#include <worker/render.hpp>

void renderSvg(unsigned int root) {
  std::stringstream ss;
  for (auto v : range_pair(boost::vertices(theGraph))) {
    if (theGraph[v].id == root) {
      svg::render(theGraph, v, ss);
      response::respond(response::SVG, "fragment", ss.str().c_str());
      return;
    }
  }

  response::error("The branch supplied for rendering was not found");
}

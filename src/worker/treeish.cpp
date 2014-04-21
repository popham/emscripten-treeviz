#include "treeish.hpp"

#include <sstream>
#include <algorithm>

#include <rapidjson/reader.h>

#include "layout.hpp"
#include "bound_buffer.hpp"
#include "builder.hpp"
#include "response.hpp"
#include "request.hpp"

typedef rapidjson::StringStream Stream;

bool Treeish::contains(typename Graph::vertex_descriptor vertex) const {
  if (!_pGraph) { return false; }

  return std::any_of(boost::vertices(*_pGraph).first,
                     boost::vertices(*_pGraph).second,
                     [&] (typename Graph::vertex_descriptor v) {
                       return v == vertex;
                    });
}

bool Treeish::contains(typename Graph::vertex_descriptor source,
                       typename Graph::vertex_descriptor target) const {
  if (!_pGraph) { return false; }

  return std::any_of(boost::edges(*_pGraph).first,
                     boost::edges(*_pGraph).second,
                     [&] (typename Graph::edge_descriptor e) {
                       return boost::source(e, *_pGraph) == source
                         && boost::target(e, *_pGraph) == target;
                    });
}

void Treeish::printVertices(std::ostream & target) const {
  if (_pGraph) {
    for (auto v : range_pair(boost::vertices(*_pGraph))) {
      target << v << std::endl;
    }
  }
}

void Treeish::printEdges(std::ostream & target) const {
  if (_pGraph) {
    for (auto e : range_pair(boost::edges(*_pGraph))) {
      target << "("
             << boost::source(e, *_pGraph)
             << ","
             << boost::target(e, *_pGraph)
             << ")" << std::endl;
    }
  }
}

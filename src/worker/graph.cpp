#include "graph.hpp"

#include "response.hpp"

bool contains(typename Graph::vertex_descriptor vertex) {
  return std::any_of(boost::vertices(theGraph).first,
                     boost::vertices(theGraph).second,
                     [&] (typename Graph::vertex_descriptor v) {
                       return v == vertex;
                    });
}

bool contains(typename Graph::vertex_descriptor source,
                       typename Graph::vertex_descriptor target) {
  return std::any_of(boost::edges(theGraph).first,
                     boost::edges(theGraph).second,
                     [&] (typename Graph::edge_descriptor e) {
                       return boost::source(e, theGraph) == source
                         && boost::target(e, theGraph) == target;
                    });
}

void printVertices(std::ostream & target) {
  for (auto v : range_pair(boost::vertices(theGraph))) {
    target << v << std::endl;
  }
}

void printEdges(std::ostream & target) {
  for (auto e : range_pair(boost::edges(theGraph))) {
    target << "("
           << boost::source(e, theGraph)
           << ","
           << boost::target(e, theGraph)
           << ")" << std::endl;
  }
}

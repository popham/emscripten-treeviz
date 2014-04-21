#pragma once

#include <utility>
#include <ostream>

#include <boost/graph/adjacency_list.hpp>

struct VProperties {
  unsigned int id; // add vertices with json handle.
};

struct GProperties {
  boost::adjacency_list<
    boost::vecS,
    boost::vecS,
    boost::directedS>::vertex_descriptor root;
};

using Graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::directedS,
  VProperties,
  boost::no_property,
  GProperties
  >;

using vertex_iterator = boost::graph_traits<Graph>::vertex_iterator;
using edge_iterator = boost::graph_traits<Graph>::edge_iterator;

template <typename T>
struct _range_pair {
  std::pair<T,T> pair;
  _range_pair(std::pair<T,T> p) : pair(p) {}
  T begin(void) { return pair.first; }
  T end(void) { return pair.second; }
};

template <typename T>
_range_pair<T> range_pair(std::pair<T,T> p) {
  return _range_pair<T>(p);
}

bool contains(typename Graph::vertex_descriptor vertex);
bool contains(typename Graph::vertex_descriptor source,
              typename Graph::vertex_descriptor target);
void printVertices(std::ostream & target);
void printEdges(std::ostream & target);

extern Graph theGraph;

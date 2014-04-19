#pragma once

#include <utility>

#include <boost/graph/adjacency_list.hpp>

struct VProperties {
  unsigned int id; // add vertices with json handle.
};

using Graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::directedS,
  VProperties
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

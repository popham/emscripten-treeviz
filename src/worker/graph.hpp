#pragma once

#include <utility>

#include <boost/graph/adjacency_list.hpp>

using Graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::directedS
  >;

using vertex_iterator = boost::graph_traits<Graph>::vertex_iterator;
using edge_iterator = boost::graph_traits<Graph>::edge_iterator;

namespace std{
  vertex_iterator begin(std::pair<vertex_iterator, vertex_iterator> pair);
  vertex_iterator end(std::pair<vertex_iterator, vertex_iterator> pair);
  edge_iterator begin(std::pair<edge_iterator, edge_iterator> pair);
  edge_iterator end(std::pair<edge_iterator, edge_iterator> pair);
}

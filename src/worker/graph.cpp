#include "graph.hpp"

namespace std{

  vertex_iterator begin(std::pair<vertex_iterator, vertex_iterator> pair) {
    return pair.first;
  }

  vertex_iterator end(std::pair<vertex_iterator, vertex_iterator> pair) {
    return pair.second;
  }

  edge_iterator begin(std::pair<edge_iterator, edge_iterator> pair) {
    return pair.first;
  }

  edge_iterator end(std::pair<edge_iterator, edge_iterator> pair) {
    return pair.second;
  }

}

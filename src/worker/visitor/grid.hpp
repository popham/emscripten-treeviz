#include <cassert>

#include <boost/graph/depth_first_search.hpp>
#include "../graph.hpp"

class GridVisitor : public boost::default_dfs_visitor {
public:
  GridVisitor(void) : _position() {}

  template <typename V, typename G>
  void discover_vertex(V vertex, G & graph) {
    _isLeaf = true;
    _position.depth += 1;
    graph[vertex].positions.push_back(_position);
  }

  template <typename E, typename G>
  void tree_edge(E edge, G const & graph) {
    _isLeaf = false;
  }

  template <typename E, typename G>
  void back_edge(E edge, G const & graph) const {
    assert(false);
  }

  template <typename E, typename G>
  void forward_or_cross_edge(E edge, G & graph) const {
    // Attach hypothetical position to vertex with multiple in-edges.
    Position next = _position;
    next.depth += 1;
    graph[boost::target(edge, graph)].positions.push_back(next);
  }

  template <typename V, typename G>
  void finish_vertex(V vertex, G const & graph) {
    if (_isLeaf) {
      _position.breadth += 1;
      _isLeaf = false; // Remains false while backtracking continues.
    }

    _position.depth -= 1;
  }

private:
  /*
   * Implements a virtual leaf concept.
   *
   * A vertex is considered a (virtual) leaf if it has no edges or only cross
   * and forward edges.
   */
  bool _isLeaf;

  /*
   * Registers to record current position within a grid.
   */
  Position _position;
};

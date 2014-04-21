#include <cassert>

#include <boost/graph/depth_first_search.hpp>
#include <boost/property_map/property_map.hpp>
#include "properties.hpp"

namespace visitor {

  template <typename SlotMap>
  class GridVisitor : public boost::default_dfs_visitor {
  public:
    GridVisitor(SlotMap slots) : _slots(slots), _slot() {}

    template <typename V, typename G>
    void discover_vertex(V vertex, G const & graph) {
      _isLeaf = true;
      _slots[vertex].push_back(_slot);
      _slot.depth += 1;
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
    void forward_or_cross_edge(E edge, G const & graph) {
      // Attach hypothetical position to vertex with multiple in-edges.
      _slots[boost::target(edge, graph)].push_back(_slot);
    }

    template <typename V, typename G>
    void finish_vertex(V vertex, G const & graph) {
      if (_isLeaf) {
        _slot.breadth += 1;
        _isLeaf = false; // Remains false while backtracking continues.
      }

      _slot.depth -= 1;
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
     * Register to record current position within a grid.
     */
    Slot _slot;

    /*
     * Property map for storing the hypothetical positions of each vertex.
     */
    SlotMap _slots;
  };

  template <typename G, typename SM, typename CM>
  void computeHypothetical(G const & graph,
                           typename G::vertex_descriptor root,
                           SM slots,
                           CM colors) {
    boost::depth_first_search(graph, GridVisitor<SM>(slots), colors, root);
  }

}

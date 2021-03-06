#include "hypothetical.hpp"

#include <algorithm>

#include <boost/format.hpp>
#include <worker/visitor/properties.hpp>
#include <worker/visitor/grid.hpp>

namespace svg {

  namespace _hypo {

    boost::format circle(visitor::Position const & p,
                         char const * const color) {
      return boost::format(R"(<circle cx="%s" cy="%s" r="0.1" style="color:%s"/>)")
        % p.breadth % p.depth % color;
    }

    boost::format arrow(visitor::Position const & s,
                        visitor::Position const & t,
                        char const * const color) {
      return boost::format(R"(<line x1="%s" y1="%s" x2="%s" y2="%s" style="color:%s"/>)")
        % s.breadth % s.depth % t.breadth % t.depth % color;
    }

  }

  /*
   * Show hypothetical positions in addition to consistent positions.  Edges
   * behind vertices, for asthetic reasons ;)
   */
  void hypothetical(Graph const & g,
                    typename Graph::vertex_descriptor root,
                    std::stringstream & ss) {
    visitor::Slots * pSlots = new visitor::Slots[boost::num_vertices(g)];
    visitor::Color * pColoring = new visitor::Color[boost::num_vertices(g)];
    visitor::computeHypothetical(g, root, pSlots, pColoring);
    delete[] pColoring;

    for (auto e : range_pair(boost::edges(g))) {
      auto source = pSlots[boost::source(e, g)];
      auto target = pSlots[boost::target(e, g)];

      bool first = true;
      std::for_each(source.begin(), source.end(), [&] (visitor::Slot const & s) {
        std::for_each(target.begin(), target.end(), [&] (visitor::Slot const & t) {
          ss << (first ? _hypo::arrow(s, t, "black") : _hypo::arrow(s, t, "red"));
          first = false;
        });
      });
    }

    for (auto v : range_pair(boost::vertices(g))) {
      auto slot = pSlots[v];

      bool first = true;
        std::for_each(slot.begin(), slot.end(), [&] (visitor::Slot const & s) {
          ss << (first ? _hypo::circle(s, "black") : _hypo::circle(s, "red"));
          first = false;
      });
    }

    delete[] pSlots;
  }
}

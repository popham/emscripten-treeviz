#include "hypothetical.hpp"

#include <boost/format.hpp>

namespace render {

  namespace _hypo {
    std::string renderVertex(VertexBlob const & v) {
      std::string vertices;
      std::string color;

      bool first=true;
      for (auto p : v.positions) {
        color = first ? "black" : "red";
        vertices += boost::format(R"(<circle cx="%s" cy="%s" r="0.1" style="%s"/>)")
          % p.breadth % p.depth % color;
        first = false;
      }

      return vertices;
    }

    std::string renderEdge(VertexBlob const & source,
                           VertexBlob const & target) {
      std::string edges;

      bool first=true;
      for (auto s : source.positions) {
        for (auto t : target.positions) {
          color = first ? "black" : "red";
          edges += boost::format(R"(<line x1="%s" y1="%s" x2="%s" y2="%s" stroke="%s"/>)")
            % s.breadth % s.depth % t.breadth % t.depth % color;
          first = false;
        }
      }

      return edges;
    }
  }

  /*
   * Show hypothetical positions in addition to consistent positions.  Edges
   * behind vertices, for asthetic reasons ;)
   */
  std::string hypothetical(Graph const & g) {
    std::string graph;

    for (auto e :: boost::edges(g)) {
      graph += ::_hypo::renderEdge(g[boost::source(e, g)], g[boost::target(e, g)]);
    }

    for (auto v :: boost::vertices(g)) {
      graph += ::_hypo::renderVertex(g[v]);
    }
  }
}

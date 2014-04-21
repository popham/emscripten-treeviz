#include "visitor.hpp"

using namespace visitor;

/*
 * Forward edge before chain.
 */
void install(Graph & g) {
  g.clear();

  // Predicated on vecS storage of vertices on the graph.  Otherwise, cache
  // vertex descriptors and use those to build edges.
  boost::add_vertex(g);
  boost::add_vertex(g);
  boost::add_vertex(g);

  boost::add_edge(0, 1, g);
  boost::add_edge(0, 2, g);
  boost::add_edge(2, 1, g);
}

std::vector<Slots> slots(void) {
  std::vector<Slots> ss(3);

  ss[0].push_back(Slot(0,0));
  ss[1].push_back(Slot(0,1));
  ss[2].push_back(Slot(1,1));
  ss[1].push_back(Slot(1,2));

  return ss;
}

#include "visitor.hpp"

/*
 * Forward edge after chain.
 */
void install(Graph & g) {
  g.clear();

  boost::add_vertex(g);
  boost::add_vertex(g);
  boost::add_vertex(g);

  boost::add_edge(0, 1, g);
  boost::add_edge(1, 2, g);
  boost::add_edge(0, 2, g);
}

std::vector<Slots> slots(void) {
  std::vector<Slots> ss(3);
  ss[0].push_back(Slot(0,0));
  ss[1].push_back(Slot(0,1));
  ss[2].push_back(Slot(0,2));
  ss[2].push_back(Slot(1,1));

  return ss;
}

#include "visitor.hpp"

using namespace visitor;

/*
 * The tree of boredom.
 */
void install(Graph & g) {
  g.clear();

  boost::add_vertex(g);
  boost::add_vertex(g);
  boost::add_vertex(g);
  boost::add_vertex(g);
  boost::add_vertex(g);
  boost::add_vertex(g);

  boost::add_edge(0, 1, g);
  boost::add_edge(0, 2, g);
  boost::add_edge(1, 3, g);
  boost::add_edge(1, 4, g);
  boost::add_edge(2, 5, g);
  boost::add_edge(2, 6, g);
}

std::vector<Slots> slots(void) {
  std::vector<Slots> ss(7);
  ss[0].push_back(Slot(0,0));
  ss[1].push_back(Slot(0,1));
  ss[2].push_back(Slot(2,1));
  ss[3].push_back(Slot(0,2));
  ss[4].push_back(Slot(1,2));
  ss[5].push_back(Slot(2,2));
  ss[6].push_back(Slot(3,2));

  return ss;
}

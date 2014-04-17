#include "visitor.hpp"

#include <boost/graph/depth_first_search.hpp>
#include <lest/lest.hpp>
#include "../grid.hpp"

Graph g;
Color * pColors=0;
Slots * pSlots=0;

lest::test tests[] =
{
  "The GridVisitor pass yields the sought hypothetical positions", []
  {
    // Build data structure. For testing, add the graph's root first, otherwise
    // find the graph's root and provide its descriptor instead of 0.
    install(g);
    pColors = new Color[boost::num_vertices(g)];
    pSlots = new Slots[boost::num_vertices(g)];
    computeHypothetical(g, 0, pSlots, pColors);
    std::vector<Slots> sought = slots();

    EXPECT(sought.size() == boost::num_vertices(g));
    for (unsigned int i=0; i<sought.size(); ++i) {
      EXPECT(sought[i] == pSlots[i]);
    }
  }
};

int main(void)
{
  return lest::run(tests);
}

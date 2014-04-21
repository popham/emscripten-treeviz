#include "visitor.hpp"

#include <algorithm>
#include <boost/graph/depth_first_search.hpp>
#include <lest/lest.hpp>
#include "../grid.hpp"

Graph g;
visitor::Color * pColors=0;
visitor::Slots * pSlots=0;

lest::test tests[] =
{
  "The GridVisitor pass yields the sought slots", []
  {
    // Build data structure. For testing, add the graph's root first, otherwise
    // find the graph's root and provide its descriptor instead of 0.
    install(g);
    pColors = new visitor::Color[boost::num_vertices(g)];
    pSlots = new visitor::Slots[boost::num_vertices(g)];
    computeHypothetical(g, 0, pSlots, pColors);
    delete[] pColors;
    std::vector<visitor::Slots> sought = slots();

    EXPECT(sought.size() == boost::num_vertices(g));
    EXPECT(std::equal(sought.begin(), sought.end(), pSlots));
    delete[] pSlots;
  }
};

int main(void)
{
  return lest::run(tests);
}

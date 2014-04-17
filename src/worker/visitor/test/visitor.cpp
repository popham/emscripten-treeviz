#include "visitor.hpp"

#include <boost/graph/depth_first_search.hpp>
#include <lest/lest.hpp>
#include "../grid.hpp"

Graph g;
VertexMap vertices;
PositionMap grid;
#include <iostream>
lest::test tests[] =
{
  "The GridVisitor pass yields the sought hypothetical positions", []
  {
    g.clear();
    install(g, vertices, grid);
    ColorMap colors(vertices.size());
    boost::depth_first_visit(g, vertices[0], GridVisitor(), colors);

    for (auto ps : grid) {
      auto descriptor = vertices[ps.first];
std::cout << "sought (" << typeid(ps.second).name() << "): " << ps.second << std::endl;
std::cout << "result full (" << typeid(g[descriptor].positions).name() << "): " << g[descriptor].positions << std::endl;
std::cout << "result first: " << std::endl;

      EXPECT(g[descriptor].positions == ps.second);
    }
  }
    };

int main(void)
{
    return lest::run(tests);
}

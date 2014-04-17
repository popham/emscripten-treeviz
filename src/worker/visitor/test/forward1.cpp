#include "visitor.hpp"

/*
 * Forward edge before chain.
 */
void install(Graph & g, VertexMap & vs, PositionMap & grid) {
  boost::get(vertex_index, g)vs[1] = boost::add_vertex(g); // vertex_index property instead
  vs[2] = boost::add_vertex(g);
  vs[3] = boost::add_vertex(g);

  boost::add_edge(vs[1], vs[2], g);
  boost::add_edge(vs[1], vs[3], g);
  boost::add_edge(vs[3], vs[2], g);

  grid[1].push_back(Position(0,0));
  grid[2].push_back(Position(0,1));
  grid[3].push_back(Position(1,1));
  grid[2].push_back(Position(2,1));
}

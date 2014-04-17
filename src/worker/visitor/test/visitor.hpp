#include <map>

#include "../../treeish.hpp"

typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef std::map<unsigned int, Vertex> VertexMap;
typedef std::map<unsigned int, Positions> PositionMap;

extern void install(Graph &, VertexMap & vertices, PositionMap & grid);

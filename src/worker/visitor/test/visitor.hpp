#include <worker/graph.hpp>
#include "../properties.hpp"

typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

extern void install(Graph &);
extern std::vector<Slots> slots(void);

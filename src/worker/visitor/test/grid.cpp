
// Forward edge after chain.
std::map<Vertex, unsigned int> grid;
Graph forward2;

v1 = boost::add_vertex(forward2);     grid[1] = v1;
v = boost::add_vertex(forward2);      grid[2] = v;
boost::add_edge(v1, v, forward2);
v2 = boost::add_vertex(forward2);     grid[3] = v2;
boost::add_edge(v, v2, forward2);

boost::add_edge(v1, v2, forward2);

// Tree
std::map<Vertex, unsigned int> grid;
Graph tree;

v1 = boost::add_vertex(tree);     grid[1] = v1;

v = v1;
v2 = boost::add_vertex(tree);     grid[2] = v2;
boost::add_edge(v, v2, tree);
v = v2;
v2 = boost::add_vertex(tree);     grid[4] = v2;
boost::add_edge(v, v2, tree);
v2 = boost::add_vertex(tree);     grid[5] = v2;
boost::add_edge(v, v2, tree);

v = v1;
v2 = boost::add_vertex(tree);     grid[3] = v2;
boost::add_edge(v, v2, tree);
v = v2;
v2 = boost::add_vertex(tree);     grid[6] = v2;
boost::add_edge(v, v2, tree);
v2 = boost::add_vertex(tree);     grid[7] = v2;
boost::add_edge(v, v2, tree);

// Cross edges (add root of two branches last).
std::map<Vertex, unsigned int> grid;
Graph cross;
Vertex b1, b2;

b1 = boost::add_vertex(cross);     grid[2] = b1;
v1 = boost::add_vertex(cross);     grid[3] = v1;
boost::add_edge(b1, v1, cross);
v2 = boost::add_vertex(cross);     grid[4] = v2;
boost::add_edge(b1, v2, cross);

b2 = boost::add_vertex(cross);     grid[5] = b2;
boost::add_edge(b2, v1, cross);
boost::add_edge(b2, v2, cross);
v = boost::add_vertex(cross);      grid[6] = v;
boost::add_edge(b2, v, cross);

v = boost::add_vertex(cross);      grid[1] = v;
boost::add_edge(v, b1, cross);
boost::add_edge(v, b2, cross);

// A small mess.
std::map<Vertex, unsigned int> grid;
Graph mess;

b1 = boost::add_vertex(mess);     grid[1] = ;

v2 = boost::add_vertex(mess);     grid[2] = ;
boost::add_edge(b1, v2, mess);
v = v2;
v2 = boost::add_vertex(mess);     grid[5] = ;
boost::add_edge(v, v2, mess);

b2 = boost::add_vertex(mess);     grid[3] = ;
boost::add_edge(b1, b2, mess);
boost::add_edge(b2, v, mess);
v = boost::add_vertex(mess);      grid[6] = ;
boost::add_edge(b2, v, mess);

b2 = boost::add_vertex(mess);     grid[4] = ;
boost::add_edge(b1, b2, mess);
boost::add_edge(b2, v2, mess);
boost::add_edge(b2, v, mess);

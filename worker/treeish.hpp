#pragma once

#include <string>

#include <boost/graph/adjacency_list.hpp>

struct CanonicalPosition {
  int i;
  int j;
};

typedef boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::directedS,
  CanonicalPosition
  > Graph;

/*
 * The input data structure should be of the form:
 * [
 *   { ...
 *        "someIdKey" : 123
 *     ...
 *       "someParentArray" : [
 *         { ...
 *               "someIdKey" : 246
 *           ...
 *         },
 *         ...
 *       ]
 *     ...
 *   },
 *   ...
 * ]
 * Specifically, keys should be of integral type (Rapidjson handles up to 64 bit
 * unsigned integrals).  Note that the general form of the parent data structure
 * is shown above; integral keys may be stored as the immediate values of
 * "someParentArray"--use an empty `parentId` path in such a case.
 */
class Treeish {
  typedef boost::graph_traits<Graph>::vertices_size_type v_size;
public:
  typedef boost::graph_traits<Graph>::vertex_iterator VIterator;
  typedef boost::graph_traits<Graph>::edge_iterator EIterator;

  Treeish(void);

  void inject(char const * const json);
  void load(std::string const & url);
  void scale(const double depth, const double breadth);
  void setPhysics(void);
  void iterate(const unsigned int count);
  void renderSvg(void) const;
  void stop(void);

  void clear(void);
  VIterator vBegin(void) const;
  VIterator vEnd(void) const;
  EIterator eBegin(void) const;
  EIterator eEnd(void) const;

  v_size nVertices(void) const;
  v_size nEdges(void) const;

private:
  Graph _graph;
};

#pragma once

#include "graph.hpp"

extern void renderSvg(Graph const &,
                      typename Graph::vertex_descriptor root,
                      std::stringstream &);

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
public:
  Treeish(void);

  void inject(char const * const);
  void load(char const * const url);
  void scale(const double depth, const double breadth);
  void setPhysics(void);
  void iterate(const unsigned int count);
  void renderSvg(void) const;
  void stop(void);

  void clear(void);
  unsigned int nVertices(void) const;
  unsigned int nEdges(void) const;
  bool contains(typename Graph::vertex_descriptor vertex) const;
  bool contains(typename Graph::vertex_descriptor source,
                typename Graph::vertex_descriptor target) const;

private:
  Graph _graph;
  typename Graph::vertex_descriptor _root;
};

#pragma once

#include <ostream>

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
  ~Treeish(void);

  // export for test use:
  bool contains(typename Graph::vertex_descriptor vertex) const;
  bool contains(typename Graph::vertex_descriptor source,
                typename Graph::vertex_descriptor target) const;
  void printVertices(std::ostream & target) const;
  void printEdges(std::ostream & target) const;

private:
  Graph * _pGraph;
  typename Graph::vertex_descriptor _root;
};

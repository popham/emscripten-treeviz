#pragma once

#include <map>
#include <string>
#include <vector>

#include <rapidjson/reader.h>
#include "stream.hpp"
#include "treeish.hpp"
#include "matching.hpp"

/*
 * Match the path to a key with unsigned int value.  Upon finding a match
 * `Match` handler is called.  No error results if no match is found.
 *
 * arrayBase : Path to a JSON array that contains parents of a vertex.
 * id : Path from `arrayBase` to a JSON leaf identifying a vertex.
 */
class MatchingHandler : public rapidjson::BaseReaderHandler<> {
public:
  MatchingHandler(Path const & id);
  MatchingHandler(Path const & arrayBase, Path const & id);

  void StartObject(void);
  void String(Ch const * pValue, rapidjson::SizeType length, bool isCopy);
  void Uint(unsigned int value);
  void EndObject(rapidjson::SizeType);

  virtual void Match(unsigned int value)=0;
  virtual void EndRoot(void) {}

  bool parse(Stream & source);
  std::string status(void) const;

private:
  Matcher _arrayBase;
  Matcher _id;
  bool _isKeyNext;
};

class VertexPass : public MatchingHandler {
  typedef std::vector<Graph::vertex_descriptor> VertexOrder;
  typedef std::map<unsigned int, Graph::vertex_descriptor> VertexLookup;

public:
  typedef VertexOrder::const_iterator const_iterator;

  VertexPass(Graph * const pGraph, Path const & id);
  virtual void Match(unsigned int value);

  const Graph::vertex_descriptor lookup(unsigned int id);
  const_iterator begin(void) const;
  const_iterator end(void) const;

private:
  Graph * const _pGraph;
  VertexLookup _table;
  VertexOrder _vertices;
};

class EdgePass : public MatchingHandler {
public:
  EdgePass(Graph * const pGraph,
           VertexPass * const pVertices,
           Path const & arrayBase,
           Path const & id);
  virtual void Match(unsigned int value);
  virtual void EndRoot(void);

private:
  Graph * const _pGraph;
  VertexPass * const _pVertices;
  VertexPass::const_iterator _currentVertex;
};

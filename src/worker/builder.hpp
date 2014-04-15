#pragma once

#include <map>
#include <string>
#include <vector>

#include <rapidjson/reader.h>
#include "stream.hpp"
#include "treeish.hpp"
#include "matching.hpp"

/*
 * From a JSON array root, match the path to a key with unsigned int value.
 * Upon finding a match, the `Match` handler is called.  No error results if a
 * match is not found.
 *
 * To match data within a nested array, call `push_path` to locate the nested
 * array and then `push_path` to locate the data within the array--however many
 * paths may be `push_path`'d as needed to match deeply nested data.
 */
class MatchingHandler : public rapidjson::BaseReaderHandler<> {
  typedef std::vector<Matcher> Matchers;
public:
  MatchingHandler(void);
  void push_path(Path const &);

  void StartArray(void);
  void EndArray(rapidjson::SizeType);
  void StartObject(void);
  void EndObject(rapidjson::SizeType);
  void String(Ch const * pValue, rapidjson::SizeType length, bool isCopy);
  void Uint(unsigned int value);

  virtual void Match(unsigned int value)=0;
  virtual void EndRoot(void) {}

  bool parse(Stream & source);
  bool isMatch(void) const;

private:
  Matchers _matchers;
  int _currentMatcher;
  bool _isKeyNext;
};

class VertexPass : public MatchingHandler {
  typedef std::vector<Graph::vertex_descriptor> VertexOrder;
  typedef std::map<unsigned int, Graph::vertex_descriptor> VertexLookup;

public:
  typedef VertexOrder::const_iterator const_iterator;

  VertexPass(Graph * const pGraph,
             Path const & path);

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
           Path const & base,
           Path const & path);
  virtual void Match(unsigned int value);
  virtual void EndRoot(void);

private:
  Graph * const _pGraph;
  VertexPass * const _pVertices;
  VertexPass::const_iterator _currentVertex;
};

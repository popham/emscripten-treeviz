#pragma once

#include <map>
#include <string>
#include <vector>
#include <stack>

#include <rapidjson/reader.h>
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

  bool isMatch(void) const;

private:
  Matchers _matchers;
  int _currentMatcher;
  bool _isKeyNext;
};

class VertexPass : public MatchingHandler {
public:
  VertexPass(Graph * const pGraph,
             Path const & path);

  virtual void Match(unsigned int value);

private:
  Graph * const _pGraph;
};

class EdgePass : public MatchingHandler {
public:
  typedef std::stack<Graph::vertex_descriptor> VertexS;

  EdgePass(Graph * const pGraph,
           Path const & base,
           Path const & path);
  virtual void Match(unsigned int value);
  virtual void EndRoot(void);
  VertexS const & parentless(void) const;

private:
  Graph * const _pGraph;

  /*
   * The multipass iterator concept guarantees that the vertices are arranged
   * in the data stream's sequence.
   */
  Graph::vertex_iterator _currentVertex;
  VertexS _parentless;
  std::map<unsigned int, Graph::vertex_descriptor> _descriptors;
  bool _isParentFound;
};

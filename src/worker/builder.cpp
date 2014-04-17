#include "builder.hpp"

#include "layout.hpp"

MatchingHandler::MatchingHandler(void) :
  _currentMatcher(-1),
  _isKeyNext(false) {}

void MatchingHandler::push_path(Path const & path) {
  _matchers.push_back(path);
}

void MatchingHandler::StartArray(void) {
  _currentMatcher += 1;
}

void MatchingHandler::EndArray(rapidjson::SizeType count) {
  _currentMatcher -= 1;
  if (_currentMatcher < _matchers.size()) {
    _isKeyNext = _matchers[_currentMatcher].depth() > 0;
  }
}

void MatchingHandler::StartObject(void) {
  if (_currentMatcher < _matchers.size()) {
    _isKeyNext = true;

    // Prepare stack for reentrant case handling.  Fine since empty keys are
    // forbidden by JSON.
    _matchers[_currentMatcher].push("");
  }
}

void MatchingHandler::EndObject(rapidjson::SizeType size) {
  if (_currentMatcher < _matchers.size()) {
    // Nonzero depth implies we're still in an object.
    _isKeyNext = _matchers[_currentMatcher].pop() > 0;
  }
}

void MatchingHandler::String(Ch const * pValue,
                             rapidjson::SizeType length,
                             bool isCopy) {
  // Insufficient information to determine whether key or value if a matcher is
  // not active.
  if (_currentMatcher < _matchers.size()) {
    std::string value(pValue, length);

    if (_isKeyNext) {
      _isKeyNext = false;
      _matchers[_currentMatcher].pop();
      _matchers[_currentMatcher].push(value);
    } else {
      _isKeyNext = true;
      // Do nothing on non-key strings.
    }
  }
}

void MatchingHandler::Uint(unsigned int value) {
  if (_currentMatcher < _matchers.size()) {
    if (isMatch()) {
      Match(value);
    }

    _isKeyNext = _matchers[_currentMatcher].depth() > 0;
  }
}

bool MatchingHandler::isMatch(void) const {
  if (_currentMatcher >= _matchers.size()) {
    return false;
  }

  bool ok=true;
  for (auto i : _matchers) { ok &= i.isMatch(); }

  return ok;
}

VertexPass::VertexPass(Graph * const pGraph,
                       Path const & path) :
  _pGraph(pGraph)
{
  push_path(path);
}

void VertexPass::Match(unsigned int value) {
  Graph::vertex_descriptor next = boost::add_vertex(/* vertexProperties, */
                                                    *_pGraph);
  _table[value] = next;
  _vertices.push_back(next);
}

const Graph::vertex_descriptor VertexPass::lookup(unsigned int id) {
  return _table[id];
}

VertexPass::const_iterator VertexPass::begin(void) const {
  return _vertices.begin();
}

VertexPass::const_iterator VertexPass::end(void) const {
  return _vertices.end();
}

EdgePass::EdgePass(Graph * const pGraph,
                   VertexPass * const pVertices,
                   Path const & parentsRoot,
                   Path const & id) :
  _pGraph(pGraph),
  _pVertices(pVertices),
  _currentVertex(pVertices->begin())
{
  push_path(parentsRoot);
  push_path(id);
}

void EdgePass::Match(unsigned int value) {
  boost::add_edge(_pVertices->lookup(value), *_currentVertex,
                  /* edgeProperties, */
                  *_pGraph);
}

void EdgePass::EndRoot(void) { ++_currentVertex; }

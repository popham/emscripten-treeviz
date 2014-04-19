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

    /*
     * Prepare stack for reentrant case handling.  Fine since empty keys are
     * forbidden by JSON.
     */
    _matchers[_currentMatcher].push("");
  }
}

void MatchingHandler::EndObject(rapidjson::SizeType size) {
  // Ignore uncharted stuff.
  if (_currentMatcher < _matchers.size()) {
    /*
     * Nonzero depth implies we're still in an object (matchers cannot cross
     * array boundaries).
     */
    if (_matchers[_currentMatcher].pop() > 0) {
      _isKeyNext = true;
    } else if (_currentMatcher == 0) {
      // Root of paths and not inside object => trigger EndRoot()
      EndRoot();
    }
  }
}

void MatchingHandler::String(Ch const * pValue,
                             rapidjson::SizeType length,
                             bool isCopy) {
  /*
   * Insufficient information to determine whether key or value if a matcher is
   * not active.
   */
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
  auto v = boost::add_vertex(*_pGraph);
  (*_pGraph)[v].id = value;
}

EdgePass::EdgePass(Graph * const pGraph,
                   Path const & parentsRoot,
                   Path const & id) :
  _pGraph(pGraph),
  _currentVertex(boost::vertices(*pGraph).first),
  _isParentFound(false)
{
  push_path(parentsRoot);
  push_path(id);

  _parentless.push(*_currentVertex); // Remove if a parent has been found.

  for (auto v : range_pair(boost::vertices(*_pGraph))) {
    _descriptors[(*_pGraph)[v].id] = v;
  }
}

void EdgePass::Match(unsigned int value) {
  boost::add_edge(_descriptors[value], *_currentVertex, *_pGraph);
  if (!_isParentFound) {
    // Match implies parent found, but only pop once.
    _isParentFound = true;
    _parentless.pop();
  }
}

void EdgePass::EndRoot(void) {
  if (++_currentVertex != boost::vertices(*_pGraph).second) {
    // Don't push end onto the stack--it doesn't exist.
    _parentless.push(*_currentVertex);
  }

  // Set flag for next object.
  _isParentFound = false;
}

EdgePass::VertexS const & EdgePass::parentless(void) const {
  return _parentless;
}

#include "matching.hpp"

const Path Path::empty = Path(0,0);

Matcher::Matcher(Path const & soughtPath) :
  _soughtPath(soughtPath),
  _matchEnd(0),
  _depthEnd(0) {}

unsigned int Matcher::push(std::string const & key) {
  // First condition: We have a match so far.
  // Second condition: We don't have a complete match.
  if (_matchEnd == _depthEnd && _matchEnd < _soughtPath.size()) {
    if (_soughtPath[_matchEnd] == key) {
      _matchEnd += 1;
    }
  }

  _depthEnd += 1;

  return _depthEnd;
}

unsigned int Matcher::pop(void) {
  _depthEnd -= 1;
  if (_matchEnd > _depthEnd) {
    _matchEnd = _depthEnd;
  }

  return _depthEnd;
}

// This depth is the current object's distance from the array root.
unsigned int Matcher::depth(void) {
  // _depthEnd refers to path depth.
  return _depthEnd;
}

bool Matcher::isMatch(void) const {
  return _depthEnd == _matchEnd && _matchEnd == _soughtPath.size();
}

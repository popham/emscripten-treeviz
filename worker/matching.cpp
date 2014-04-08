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

// Wild card semantics for any paths deeper than the sought path.
bool Matcher::isMatch(void) const {
  return _matchEnd == _soughtPath.size();
}

bool Matcher::isExactMatch(void) const {
  return isMatch() && _depthEnd == _soughtPath.size();
}

std::string Matcher::status(void) const {
  return "_matchEnd: " + std::to_string(_matchEnd) + "\n_depthEnd: " + std::to_string(_depthEnd) + "\n";
}

#pragma once

#include <string>

class Path {
public:
  Path(char const * const * const data, unsigned int length) :
    _data(data),
    _length(length) {}
  unsigned int size(void) const                       { return _length; }
  char const * const operator[](unsigned int i) const { return _data[i]; }
  static const Path empty;

private:
  char const * const * const _data;
  unsigned int _length;
};

// Matches don't cross array boundaries.
// Accommodate match from some root.
class Matcher {
public:
  Matcher(Path const & soughtPath);

  unsigned int push(std::string const & key);
  unsigned int pop(void);

  // Wild card semantics for any paths deeper than the sought path.
  bool isMatch(void) const;
  // Non-wild card semantics.
  bool isExactMatch(void) const;
  std::string status(void) const;

private:
  Path const & _soughtPath;
  unsigned int _matchEnd;
  unsigned int _depthEnd;
};

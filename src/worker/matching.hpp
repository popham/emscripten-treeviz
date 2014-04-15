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

// Matches don't cross array boundaries.  A depth of zero therefore implies
// array context and nonzero depth implies object context.
class Matcher {
public:
  Matcher(Path const & soughtPath);

  // Return post-operation depths.
  unsigned int push(std::string const & key);
  unsigned int pop(void);
  unsigned int depth(void);

  bool isMatch(void) const;

private:
  Path const & _soughtPath;
  unsigned int _matchEnd;
  unsigned int _depthEnd;
};

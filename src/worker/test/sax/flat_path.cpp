#include <worker/layout.hpp>

char const * const vPathRaw[] = {
  static_cast<char const * const>("id")
};

char const * const eBaseRaw[] = {
  static_cast<char const * const>("parents")
};
char const * const ePathRaw[] = {};

const Path vertexPath(&vPathRaw[0], 1);
const Path parentsBase(&eBaseRaw[0], 1);
const Path parentsPath(&ePathRaw[0], 0);

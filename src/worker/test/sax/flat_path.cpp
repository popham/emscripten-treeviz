#include <worker/layout.hpp>

char const * const vPathRaw[] = {
  static_cast<char const * const>("id")
};

char const * const eBaseRaw[] = {
  static_cast<char const * const>("parents")
};
char const * const ePathRaw[] = {};

const Path theVertexPath(&vPathRaw[0], 1);
const Path theParentsBase(&eBaseRaw[0], 1);
const Path theParentsPath(&ePathRaw[0], 0);

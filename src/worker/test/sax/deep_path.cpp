#include <worker/layout.hpp>

char const * const vPathRaw[] = {
  static_cast<char const * const>("layer1"),
  static_cast<char const * const>("layer2"),
  static_cast<char const * const>("id")
};

char const * const eBaseRaw[] = {
  static_cast<char const * const>("layer1"),
  static_cast<char const * const>("mayer2")
};
char const * const ePathRaw[] = {
  static_cast<char const * const>("mayer3"),
  static_cast<char const * const>("parentId")
};

const Path theVertexPath(&vPathRaw[0], 3);
const Path theParentsBase(&eBaseRaw[0], 2);
const Path theParentsPath(&ePathRaw[0], 2);

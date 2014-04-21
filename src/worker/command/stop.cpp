#include "command.hpp"

void stop(void) {
  theGraph.clear();

  response::clean();
}

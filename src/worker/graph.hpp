#pragma once

#include <boost/graph/adjacency_list.hpp>

using Graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::directedS
  >;

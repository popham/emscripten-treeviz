#include  "../command.hpp"

#include <rapidjson/reader.h>
#include <worker/builder.hpp>

unsigned int computeRoot(void) {
  bool * pParentExists = new bool[boost::num_vertices(theGraph)];

  for (auto v : range_pair(boost::vertices(theGraph))) {
    // Initialize to false.
    pParentExists[v] = false;
  }

  for (auto e : range_pair(boost::edges(theGraph))) {
    pParentExists[boost::target(e,theGraph)] = true;
  }

  unsigned int rootCount=0;
  for (auto v : range_pair(boost::vertices(theGraph))) {
    if (!pParentExists[v]) {
      ++rootCount;
      theGraph[boost::graph_bundle].root = v;
    }
  }

  delete[] pParentExists;

  return rootCount;
}

void inject(char const * const json) {
  rapidjson::Reader reader;

  rapidjson::StringStream is(json);
  VertexPass vp(&theGraph, theVertexPath);
  if (!reader.Parse<rapidjson::kParseDefaultFlags>(is, vp)) {
    theGraph.clear();
    response::log("Serialization of vertex data to data structure failed");
    response::error(reader.GetParseError());
    return;
  }

  is = rapidjson::StringStream(json); // Reset stream.
  EdgePass ep(&theGraph, theParentsBase, theParentsPath);
  if (!reader.Parse<rapidjson::kParseDefaultFlags>(is, ep)) {
    theGraph.clear();
    response::log("Serialization of edge data to data structure failed");
    response::error(reader.GetParseError());
    return;
  }

  unsigned int count = computeRoot();
  if (count == 0) {
    response::error("All of the candidate vertices have in-edges.  Provide DAG data.");
  } else if (count > 1) {
    response::error("The graph has more than one disconnected component.  Provide a single, connected DAG.");
  } else {
    response::vacuous();
  }
}

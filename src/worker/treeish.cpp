#include "treeish.hpp"

#include <sstream>
#include <algorithm>

#include <rapidjson/reader.h>

#include "layout.hpp"
#include "bound_buffer.hpp"
#include "builder.hpp"
#include "response.hpp"
#include "request.hpp"

typedef rapidjson::StringStream Stream;

Treeish::Treeish(void) : _pGraph(0) {}

Treeish::~Treeish(void) {
  if (_pGraph) { delete _pGraph; }
}

void Treeish::inject(char const * const json) {
  if (_pGraph) { delete _pGraph; }

  _pGraph = new Graph();
  rapidjson::Reader reader;

  Stream is(json);
  VertexPass vp(_pGraph, vertexPath);
  if (!reader.Parse<rapidjson::kParseDefaultFlags>(is, vp)) {
    delete _pGraph;
    _pGraph = 0;

    response::log("Serialization of vertex data to data structure failed");
    response::error(reader.GetParseError());

    return;
  }

  is = Stream(json);
  EdgePass ep(_pGraph, parentsBase, parentsPath);
  if (!reader.Parse<rapidjson::kParseDefaultFlags>(is, ep)) {
    delete _pGraph;
    _pGraph = 0;

    response::log("Serialization of edge data to data structure failed");
    response::error(reader.GetParseError());

    return;
  }

  if (ep.parentless().size() == 1)
    _root = ep.parentless().top();
  else if (ep.parentless().size() == 0) {
    response::error("All of the candidate vertices have in-edges.  Provide DAG data.");
  } else {
    response::error("The graph has more than one disconnected component.  Provide a single, connected DAG.");
  }

  response::vacuous();
}

void Treeish::load(char const * const url) {
  bound_buffer bb;
  getJson(&bb, url);
  /*
  if (failed) {
    response::errorish(std::string(bb.first, bb.length));
    free(bb.first);
  }
  */
  inject(bb.first);
  dealloc_bound_buffer(&bb);
}

void Treeish::scale(const double depth, const double breadth) { response::vacuous(); }

void Treeish::setPhysics(void) { response::vacuous(); }

void Treeish::iterate(const unsigned int count) { response::vacuous(); }

void Treeish::renderSvg(void) const {
  if (_pGraph) {
    std::stringstream ss;
    ::renderSvg(*_pGraph, _root, ss);
    response::respond(response::SVG, "fragment", ss.str().c_str());
  } else {
    response::respond(response::SVG, "fragment", "");
  }
}

void Treeish::stop(void) {
  if (_pGraph) {
    _pGraph->clear();
  }

  response::clean();
}

unsigned int Treeish::nVertices(void) const {
  if (!_pGraph) { return 0; }

  return boost::num_vertices(*_pGraph);
}

unsigned int Treeish::nEdges(void) const {
  if (!_pGraph) { return 0; }

  return boost::num_edges(*_pGraph);
}

bool Treeish::contains(typename Graph::vertex_descriptor vertex) const {
  if (!_pGraph) { return false; }

  return std::any_of(boost::vertices(*_pGraph).first,
                     boost::vertices(*_pGraph).second,
                     [&] (typename Graph::vertex_descriptor v) {
                       return v == vertex;
                    });
}

bool Treeish::contains(typename Graph::vertex_descriptor source,
                       typename Graph::vertex_descriptor target) const {
  if (!_pGraph) { return false; }

  return std::any_of(boost::edges(*_pGraph).first,
                     boost::edges(*_pGraph).second,
                     [&] (typename Graph::edge_descriptor e) {
                       return boost::source(e, *_pGraph) == source
                         && boost::target(e, *_pGraph) == target;
                    });
}

void Treeish::printVertices(std::ostream & target) const {
  if (_pGraph) {
    for (auto v : range_pair(boost::vertices(*_pGraph))) {
      target << v << std::endl;
    }
  }
}

void Treeish::printEdges(std::ostream & target) const {
  if (_pGraph) {
    for (auto e : range_pair(boost::edges(*_pGraph))) {
      target << "("
             << boost::source(e, *_pGraph)
             << ","
             << boost::target(e, *_pGraph)
             << ")" << std::endl;
    }
  }
}

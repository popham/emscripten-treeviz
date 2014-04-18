#include "treeish.hpp"

#include <sstream>
#include <algorithm>

#include <rapidjson/reader.h>

#include "layout.hpp"
#include "stream.hpp"
#include "bound_buffer.hpp"
#include "builder.hpp"
#include "response.hpp"
#include "request.hpp"

Treeish::Treeish(void) : _graph() {}

void Treeish::inject(char const * const json) {
  rapidjson::Reader reader;

  Stream is(json);
  VertexPass vp(&_graph, vertexPath);
  if (!reader.Parse<rapidjson::kParseDefaultFlags>(is, vp)) {
    _graph.clear();
    response::log("Serialization of vertex data to data structure failed");
    response::error(reader.GetParseError());
  }

  is = Stream(json);
  EdgePass ep(&_graph, &vp, parentsBase, parentsPath);
  if (!reader.Parse<rapidjson::kParseDefaultFlags>(is, ep)) {
    _graph.clear();
    response::log("Serialization of edge data to data structure failed");
    response::error(reader.GetParseError());
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
  std::stringstream ss;
  ::renderSvg(_graph, _root, ss);
  response::respond(response::SVG, "fragment", ss.str().c_str());
}

void Treeish::stop(void) {
  _graph.clear();
  response::clean();
}

void Treeish::clear(void) {
  _graph.clear();
}

unsigned int Treeish::nVertices(void) const {
  return boost::num_vertices(_graph);
}

unsigned int Treeish::nEdges(void) const {
  return boost::num_edges(_graph);
}

bool Treeish::contains(typename Graph::vertex_descriptor vertex) const {
  return std::any_of(std::begin(boost::vertices(_graph)),
                     std::end(boost::vertices(_graph)),
                     [&] (typename Graph::vertex_descriptor v) {
                       return v == vertex;
                    });
}

bool Treeish::contains(typename Graph::vertex_descriptor source,
                       typename Graph::vertex_descriptor target) const {
  return std::any_of(std::begin(boost::edges(_graph)),
                     std::end(boost::edges(_graph)),
                     [&] (typename Graph::edge_descriptor e) {
                       return boost::source(e, _graph) == source
                         && boost::target(e, _graph)==target;
                    });
}

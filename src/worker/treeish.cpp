#include "treeish.hpp"

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
  response::respond(response::SVG, "fragment", R"(<svg><circle r=\"50\"/></svg>)");
}

void Treeish::stop(void) {
  _graph.clear();
  response::clean();
}

void Treeish::clear(void) {
  _graph.clear();
}

Treeish::VIterator Treeish::vBegin(void) const {
  return boost::vertices(_graph).first;
}

Treeish::VIterator Treeish::vEnd(void) const {
  return boost::vertices(_graph).second;  
}

Treeish::EIterator Treeish::eBegin(void) const {
  return boost::edges(_graph).first;
}

Treeish::EIterator Treeish::eEnd(void) const {
  return boost::edges(_graph).second;
}

Treeish::v_size Treeish::nVertices(void) const {
  return boost::num_vertices(_graph);
}

Treeish::v_size Treeish::nEdges(void) const {
  return boost::num_edges(_graph);
}

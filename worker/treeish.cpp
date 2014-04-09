#include "treeish.hpp"

#include "layout.hpp"
#include "stream.hpp"
#include "bound_buffer.hpp"
#include "builder.hpp"
#include "response.hpp"
#include "request.hpp"

Treeish::Treeish(void) : _graph() {}

void Treeish::inject(char const * const json) {
  Stream is(const_cast<char * const>(json));
  VertexPass vp(&_graph, vertexBase, vertexPath);
  if (!vp.parse(is)) {
    _graph.clear();
    response::error("Serialization of vertex data to data structure failed");
  }

  is = Stream(const_cast<char * const>(json));
  char const * const ePath[] = {static_cast<char const * const>("parents")};
  EdgePass ep(&_graph, &vp, parentsBase, parentsPath);
  if (!ep.parse(is)) {
    _graph.clear();
    response::error("Serialization of edge data to data structure failed");
  }

  response::vacuous();
}

void Treeish::load(std::string const & url) {
  bound_buffer bb;
  get(&bb, url.c_str());
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

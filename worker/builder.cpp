#include "builder.hpp"

#include "layout.hpp"

MatchingHandler::MatchingHandler(Path const & base,
                                 Path const & path) :
  _base(base),
  _path(path),
  _isKeyNext(false) {}

void MatchingHandler::StartObject(void) {
  _isKeyNext = true;
}

void MatchingHandler::String(Ch const * pValue,
                             rapidjson::SizeType length,
                             bool isCopy) {
  std::string value(pValue, length);

  // We only care about string keys since we're looking for unsigned int values.
  if (_isKeyNext) {
    _isKeyNext = false;
    _base.push(value);

    // Only bother matching the id path once the base path has been matched.
    // The two paths are disjoint.
    if (_base.isMatch() && !_base.isExactMatch()) {
      _path.push(value);
    }
  }
}

void MatchingHandler::Uint(unsigned int value) {
  // Exact match to avoid erroneous returns given a degenerate path.
  if (_base.isMatch() && _path.isExactMatch()) {
    Match(value);
  }
  _isKeyNext = true;
}

void MatchingHandler::EndObject(rapidjson::SizeType size) {
  _isKeyNext = false; // [{}, "asdf", ...] implies a key of "asdf" without this.

  if (_base.isMatch() && !_base.isExactMatch()) {
    _path.pop();
  }

  if (_base.pop() == 0) {
    EndRoot();
  }
}

bool MatchingHandler::parse(Stream & source) {
  rapidjson::Reader reader;

  return reader.Parse<rapidjson::kParseDefaultFlags>(source, *this);
}

std::string MatchingHandler::status(void) const {
  return "_path:\n" + _path.status() + "\n_base:\n" + _base.status();
}

VertexPass::VertexPass(Graph * const pGraph,
                       Path const & base,
                       Path const & path) :
  MatchingHandler(base, path),
  _pGraph(pGraph) {}

void VertexPass::Match(unsigned int value) {
  Graph::vertex_descriptor next = boost::add_vertex(/* vertexProperties, */
                                                    *_pGraph);
  _table[value] = next;
  _vertices.push_back(next);
}

const Graph::vertex_descriptor VertexPass::lookup(unsigned int id) {
  return _table[id];
}

VertexPass::const_iterator VertexPass::begin(void) const {
  return _vertices.begin();
}

VertexPass::const_iterator VertexPass::end(void) const {
  return _vertices.end();
}

EdgePass::EdgePass(Graph * const pGraph,
                   VertexPass * const pVertices,
                   Path const & arrayBase,
                   Path const & id) :
  MatchingHandler(arrayBase, id),
  _pGraph(pGraph),
  _pVertices(pVertices),
  _currentVertex(pVertices->begin()) {}

void EdgePass::Match(unsigned int value) {
  boost::add_edge(_pVertices->lookup(value), *_currentVertex,
                  /* edgeProperties, */
                  *_pGraph);
}

void EdgePass::EndRoot(void) { ++_currentVertex; }

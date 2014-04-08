#include "builder.hpp"

#include "layout.hpp"

MatchingHandler::MatchingHandler(Path const & id) :
  _arrayBase(Path::empty),
  _id(id),
  _isKeyNext(false) {}

MatchingHandler::MatchingHandler(Path const & arrayBase, Path const & id) :
  _arrayBase(arrayBase),
  _id(id),
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
    _arrayBase.push(value);

    // Only bother matching the id path once the base path has been matched.
    // The two paths are disjoint.
    if (_arrayBase.isMatch() && !_arrayBase.isExactMatch()) {
      _id.push(value);
    }
  }
}

void MatchingHandler::Uint(unsigned int value) {
  // Exact match to avoid erroneous returns given a degenerate path.
  if (_arrayBase.isMatch() && _id.isExactMatch()) {
    Match(value);
  }
  _isKeyNext = true;
}

void MatchingHandler::EndObject(rapidjson::SizeType size) {
  _isKeyNext = false; // [{}, "asdf", ...] implies a key of "asdf" without this.

  if (_arrayBase.isMatch() && !_arrayBase.isExactMatch()) {
    _id.pop();
  }

  if (_arrayBase.pop() == 0) {
    EndRoot();
  }
}

bool MatchingHandler::parse(Stream & source) {
  rapidjson::Reader reader;

  return reader.Parse<rapidjson::kParseDefaultFlags>(source, *this);
}

std::string MatchingHandler::status(void) const {
  return "_id:\n" + _id.status() + "\n_arrayBase:\n" + _arrayBase.status();
}

VertexPass::VertexPass(Graph * const pGraph, Path const & id) : 
  MatchingHandler(id),
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

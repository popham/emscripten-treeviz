#include "accept.hpp"

#include "treeish.hpp"
#include "response.hpp"

Treeish treeish;

void accept(char const * const data, int size) {
  TreeishDispatcher dispatcher;
  dispatcher.parse(data, &treeish);
}

TreeishDispatcher::TreeishDispatcher(void) : _pContext(0) {}

bool TreeishDispatcher::parse(char const * const source, Treeish * pTreeish) {
  rapidjson::Reader reader;
  Stream is(const_cast<char * const>(source));

  // Figure out what command needs calling.
  command::WireCommandType pass1;
  _pContext = &pass1;
  if (!reader.Parse<rapidjson::kParseDefaultFlags>(is, *this)) {
    response::error("Failed to determine which command to evaluate");
    return false;
  }

  // Call the command.
  is = Stream(const_cast<char * const>(source));
  _pContext = command::WireCommand::create(pass1.type, pTreeish);
  if (!reader.Parse<rapidjson::kParseDefaultFlags>(is, *this)) {
    delete _pContext;
    response::error("Failed to bind parameters for command evaluation");
    return false;
  }

  dynamic_cast<command::WireCommand *>(_pContext)->call();
  delete _pContext;
  return true;
}

void TreeishDispatcher::String(Ch const * pValue, rapidjson::SizeType length, bool isCopy) {
  std::string value(pValue, length);

  if (_isKeyNext) {
    _isKeyNext = false;
    _key = value;
  } else {
    _isKeyNext = true;
    _pContext->bind(_key, value);
  }
}

void TreeishDispatcher::Bool(bool b)       { _handleValue(b); }
void TreeishDispatcher::Int(int i)         { _handleValue(i); }
void TreeishDispatcher::Uint(unsigned i)   { _handleValue(i); }
void TreeishDispatcher::Int64(int64_t i)   { _handleValue(i); }
void TreeishDispatcher::Uint64(uint64_t i) { _handleValue(i); }
void TreeishDispatcher::Double(double d)   { _handleValue(d); }
void TreeishDispatcher::StartObject()      { _isKeyNext = true; }

//~/emscripten/emcc -O0 -I /home/popham/include/boost_1_55_0/ -I ./rapidjson/include/ worker/dag.cpp worker/accept.cpp -o main.js -std=c++11 -s BUILD_AS_WORKER=1 -s EXPORTED_FUNCTIONS="['_accept']" --closure 1

//EMCC_FAST_COMPILER=0 ~/emscripten/emcc -I /home/popham/include/boost_1_55_0/ child/dag.cpp child/dispatcher.cpp main.cpp -o main.js -std=c++11 -s BUILD_AS_WORKER=1 -s EXPORTED_FUNCTIONS="['_accept']" --bind

//VERBOSE//EMCC_DEBUG=2 ~/emscripten/emcc -O3 -I /home/popham/include/boost_1_55_0/ -I ./rapidjson/include/ worker/dag.cpp worker/accept.cpp -o main.js -std=c++11 -s BUILD_AS_WORKER=1 -s EXPORTED_FUNCTIONS="['_accept']" --closure 1


//~/emscripten/emcc -O3 -I /home/popham/include/boost_1_55_0/ -I ./rapidjson/include/ worker/dag.cpp -o dag.js -std=c++11 -s BUILD_AS_WORKER=1 -s EXPORTED_FUNCTIONS="['_get']" --closure 1

//~/emscripten/emcc -O3 -I /home/popham/include/boost_1_55_0/ -I ./rapidjson/include/ worker/accept.cpp -o accept.js -std=c++11 -s BUILD_AS_WORKER=1 -s EXPORTED_FUNCTIONS="['_accept']" --closure 1

#include "accept.hpp"

#include <string>

#include <rapidjson/rapidjson.h>
#include "treeish.hpp"
#include "response.hpp"

Treeish treeish;
typedef rapidjson::StringStream Stream;

void accept(char const * const data, int size) {
  TreeishDispatcher dispatcher;
  dispatcher.parse(std::string(data, size).c_str(), &treeish);
}

TreeishDispatcher::TreeishDispatcher(void) :
  _pContext(0) {}

bool TreeishDispatcher::parse(char const * const source, Treeish * pTreeish) {
  rapidjson::Reader reader;
  Stream is(source);

  // Figure out what command needs calling.
  command::WireCommandType pass1;
  _pContext = &pass1;
  if (!reader.Parse<rapidjson::kParseDefaultFlags>(is, *this)) {
    response::log("Failed to determine which command to evaluate");
    response::error(reader.GetParseError());
    return false;
  }

  // Call the command.
  is = Stream(source);
  _pContext = command::WireCommand::create(pass1.type, pTreeish);
  if (!reader.Parse<rapidjson::kParseDefaultFlags>(is, *this)) {
    response::log("Failed to evaluate the command");
    response::error(reader.GetParseError());
    delete _pContext;
    return false;
  }

  dynamic_cast<command::WireCommand *>(_pContext)->call();
  delete _pContext;
  return true;
}

void TreeishDispatcher::String(Ch const * pValue, rapidjson::SizeType length, bool isCopy) {
  std::string value(pValue, length);

  if (_isOdd) {
    _key = value;
    _isOdd = false;
  } else {
    _nonKey(value);
  }
}

void TreeishDispatcher::Bool(bool b)       { _nonKey(b); }
void TreeishDispatcher::Int(int i)         { _nonKey(i); }
void TreeishDispatcher::Uint(unsigned i)   { _nonKey(i); }
void TreeishDispatcher::Int64(int64_t i)   { _nonKey(i); }
void TreeishDispatcher::Uint64(uint64_t i) { _nonKey(i); }
void TreeishDispatcher::Double(double d)   { _nonKey(d); }
void TreeishDispatcher::StartObject()      { _isOdd = true; }

void TreeishDispatcher::_nonKey(boost::any value) {
  _pContext->bind(_key, value);
  _isOdd = true;
}

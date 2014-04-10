#pragma once

#include <string>

#include <rapidjson/reader.h>
#include "stream.hpp"
#include "command.hpp"
#include "treeish.hpp"

extern Treeish treeish;

extern "C" {
  extern void accept(char const * const data, int size);
}

// Flat configuration object--no arrays or depth.
class TreeishDispatcher : public rapidjson::BaseReaderHandler<> {
public:
  TreeishDispatcher(void);

  bool parse(char const * const source, Treeish * pTreeish);

  void String(Ch const * pValue, rapidjson::SizeType length, bool isCopy);
  void Bool(bool b);
  void Int(int i);
  void Uint(unsigned i);
  void Int64(int64_t i);
  void Uint64(uint64_t i);
  void Double(double d);
  void StartObject();

private:
  command::HandlerStrategy * _pContext;
  bool _isKeyNext;
  std::string _key;

  template <typename T>
  void _handleValue(T value) {
    _pContext->bind(_key, value);
    _isKeyNext = true;
  }
};

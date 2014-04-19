#pragma once

#include <string>

#include <boost/any.hpp>
#include <rapidjson/reader.h>
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
  bool _isOdd;
  std::string _key;

  void _nonKey(boost::any value);
};

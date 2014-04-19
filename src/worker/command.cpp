#include "command.hpp"

#include "treeish.hpp"
#include "response.hpp"

namespace command {
  bool WireCommandType::bind(std::string const & name, Value value) {
    if (name == "command") {
      type = static_cast<Command>(boost::any_cast<unsigned int>(value));
      return true;
    }

    return false;
  }

  WireCommand * WireCommand::create(Command command, Treeish * const pTreeish) {
    switch (command) {
    case LOAD:        return new Load(pTreeish);
    case SCALE:       return new Scale(pTreeish);
    case SET_PHYSICS: return new SetPhysics(pTreeish);
    case ITERATE:     return new Iterate(pTreeish);
    case STOP:        return new Stop(pTreeish);
    case RENDER_SVG:  return new RenderSvg(pTreeish);
    }
  }

  void Stop::call(void) {
    _pTreeish->stop();
  }

  void RenderSvg::call(void) {
    _pTreeish->renderSvg();
  }

  bool Load::bind(std::string const & name, Value value) {
    if (name == "dataSource") {
      _url = boost::any_cast<std::string>(value);
      _complete |= 1;
      return true;
    }

    return false;
  }

  void Load::call(void) {
    if (_complete == 1) {
      _pTreeish->load(_url.c_str());
    } else {
      response::incompleteBindingError("Load");
    }
  }

  bool Scale::bind(std::string const & name, Value value) {
    if (name == "breadth") {
      _breadth = boost::any_cast<double>(value);
      _complete |= 1;
      return true;
    } else if (name == "depth") {
      _depth = boost::any_cast<double>(value);
      _complete |= 2;
      return true;
    }

    return false;
  }

  void Scale::call(void) {
    if (_complete == 3) {
      _pTreeish->scale(_depth, _breadth);
    } else {
      response::incompleteBindingError("Scale");
    }
  }

  bool SetPhysics::bind(std::string const & name, Value value) {
    return false;
  }

  void SetPhysics::call(void) {
    _pTreeish->setPhysics();
  }

  bool Iterate::bind(std::string const & name, Value value) {
    if (name == "count") {
      _count = boost::any_cast<unsigned int>(value);
      _complete |= 1;
      return true;
    }

    return false;
  }

  void Iterate::call(void) {
    if (_complete == 1) {
      _pTreeish->iterate(_count);
    } else {
      response::incompleteBindingError("Iterate");
    }
  }
}

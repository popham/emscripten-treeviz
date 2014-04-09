#include "command.hpp"

#include "treeish.hpp"
#include "response.hpp"

namespace command {
  bool WireCommandType::bind(std::string const & name, unsigned int value) {
    if (name == "command") {
      type = (Command)value;
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

  bool Load::bind(std::string const & name, std::string const & value) {
    if (name == "dataSource") {
      _url = value;
      _complete |= 1;
      return true;
    }

    return false;
  }

  void Load::call(void) {
    if (_complete == 1) {
      _pTreeish->load(_url);
    } else {
      response::incompleteBindingError("Load");
    }
  }

  bool Scale::bind(std::string const & name, double value) {
    if (name == "breadth") {
      _breadth = value;
      _complete |= 1;
      return true;
    } else if (name == "depth") {
      _depth = value;
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

  /*stub for now: bool SetPhysics::bind(std::string const & name,  value) {
    
    }*/

  void SetPhysics::call(void) {
    _pTreeish->setPhysics();
  }

  bool Iterate::bind(std::string const & name, unsigned int value) {
    if (name == "count") {
      _count = value;
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
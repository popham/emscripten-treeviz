#pragma once

#include <string>

#include <boost/any.hpp>

class Treeish;

namespace command {

  enum Command {
    LOAD        = 1,
    SCALE       = 2,
    SET_PHYSICS = 3,
    ITERATE     = 4,
    STOP        = 5,
    RENDER_SVG  = 20
  };

  typedef enum Command Command;

  class HandlerStrategy {
  public:
    typedef boost::any Value;
    virtual bool bind(std::string const & name, Value) { return false; }
  };

  class WireCommandType : public HandlerStrategy {
  public:
    Command type;
    virtual bool bind(std::string const & name, Value);
  };

  class WireCommand : public HandlerStrategy {
  public:
    WireCommand(Treeish * pTreeish) : _pTreeish(pTreeish), _complete(0) {}
    static WireCommand * create(Command command, Treeish * const pTreeish);
    virtual void call(void)=0;

  protected:
    Treeish * _pTreeish;
    int _complete;
  };

  class Stop : public WireCommand {
  public:
    using WireCommand::WireCommand;
    virtual void call(void);
  };

  class RenderSvg : public WireCommand {
  public:
    using WireCommand::WireCommand;
    virtual void call(void);
  };

  class Load : public WireCommand {
  public:
    using WireCommand::WireCommand;
    virtual bool bind(std::string const & name, Value);
    virtual void call(void);

  private:
    std::string _url;
  };

  class Scale : public WireCommand {
  public:
    using WireCommand::WireCommand;
    virtual bool bind(std::string const & name, Value);
    virtual void call(void);

  private:
    double _depth;
    double _breadth;
  };

  class SetPhysics : public WireCommand {
  public:
    using WireCommand::WireCommand;
    virtual bool bind(std::string const & name, Value);
    virtual void call(void);
  };

  class Iterate : public WireCommand {
  public:
    using WireCommand::WireCommand;
    virtual bool bind(std::string const & name, Value);
    virtual void call(void);

  private:
    unsigned int _count;
  };
}

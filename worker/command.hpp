#pragma once

#include <string>

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
    virtual bool bind(std::string const & name, std::string const & value) { return false; }
    virtual bool bind(std::string const & name, bool value) { return false; }
    virtual bool bind(std::string const & name, int value) { return false; }
    virtual bool bind(std::string const & name, unsigned int value) { return false; }
    virtual bool bind(std::string const & name, int64_t value) { return false; }
    virtual bool bind(std::string const & name, uint64_t value) { return false; }
    virtual bool bind(std::string const & name, double value) { return false; }
  };

  class WireCommandType : public HandlerStrategy {
  public:
    Command type;
    virtual bool bind(std::string const & name, unsigned int value);
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
    void call(void);
  };

  class RenderSvg : public WireCommand {
  public:
    using WireCommand::WireCommand;
    void call(void);
  };

  class Load : public WireCommand {
  public:
    using WireCommand::WireCommand;
    bool bind(std::string const & name, std::string const & value);
    void call(void);

  private:
    std::string _url;
  };

  class Scale : public WireCommand {
  public:
    using WireCommand::WireCommand;
    bool bind(std::string const & name, double value);
    void call(void);

  private:
    double _depth;
    double _breadth;
  };

  class SetPhysics : public WireCommand {
  public:
    using WireCommand::WireCommand;
    void call(void);
  };

  class Iterate : public WireCommand {
  public:
    using WireCommand::WireCommand;
    bool bind(std::string const & name, unsigned int value);
    void call(void);

  private:
    unsigned int _count;
  };
}

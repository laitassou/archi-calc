#include "Command.h"
#include "Stack.h"
#include "utility/Exception.h"


namespace mydesign
{


void Command::execute()
{
  checkPreconditionsImpl();
  executeImpl();
  return;
}

void Command::undo()
{
  undoImpl();
  return;
}

Command * Command::clone() const
{
     return cloneImpl();
}
const char* Command::helpMessage() const
{
    return helpMessageImpl();
}

void Command::deallocate()
{
    delete this;
}


void Command::checkPreconditionsImpl() const
{
    return;
}


BinaryCommand::BinaryCommand(const BinaryCommand& rhs):
Command(rhs), top_(rhs.top_), next_(rhs.next_)
{
}

BinaryCommand::~BinaryCommand()
{

}


void BinaryCommand::checkPreconditionsImpl() const
{
  if (Stack::Instance().size() <2)
  {
    throw Exception{"Stack must have 2 elements"};
  }
}


  void BinaryCommand::executeImpl() noexcept
  {
    top_ = Stack::Instance().pop(true);
    next_ = Stack::Instance().pop(true);
    Stack::Instance().push(binaryOperation(next_,top_));

    return;
  }

  void BinaryCommand::undoImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    Stack::Instance().pop(true);
    Stack::Instance().push(next_, true);
    Stack::Instance().push(top_);

    return;
}

UnaryCommand::UnaryCommand(const UnaryCommand& rhs)
: Command(rhs)
, top_(rhs.top_)
{
}

UnaryCommand::~UnaryCommand()
{ }

void UnaryCommand::checkPreconditionsImpl() const
{
    if( Stack::Instance().size() < 1 )
        throw Exception{"Stack must have one element"};
}

void UnaryCommand::executeImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    top_ = Stack::Instance().pop(true);
    Stack::Instance().push( unaryOperation(top_) );

    return;
}

void UnaryCommand::undoImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    Stack::Instance().pop(true);
    Stack::Instance().push(top_);

    return;
}



PluginCommand::~PluginCommand()
{ }

void PluginCommand::checkPreconditionsImpl() const
{
    const char* p = checkPluginPreconditions();
    if(p) throw Exception(p);

    return;
}

PluginCommand *PluginCommand::cloneImpl() const
{
    auto p = clonePluginImpl();
    if(!p) throw Exception("Problem cloning a plugin command");
    else return p;
}

BinaryCommandAlternative::BinaryCommandAlternative(const std::string& help, std::function<BinaryCommandAlternative::BinaryCommandOp> f)
: helpMsg_{help}
, command_{f}
{ }

void BinaryCommandAlternative::checkPreconditionsImpl() const
{
    if( Stack::Instance().size() < 2 )
        throw Exception{"Stack must have 2 elements"};
}

BinaryCommandAlternative::BinaryCommandAlternative(const BinaryCommandAlternative& rhs)
: Command{rhs}
, top_{rhs.top_}
, next_{rhs.next_}
, helpMsg_{rhs.helpMsg_}
, command_{rhs.command_}
{ }

const char *BinaryCommandAlternative::helpMessageImpl() const noexcept
{
    return helpMsg_.c_str();
}

BinaryCommandAlternative* BinaryCommandAlternative::cloneImpl() const
{
    return new BinaryCommandAlternative{*this};
}

void BinaryCommandAlternative::executeImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    top_ = Stack::Instance().pop(true);
    next_ = Stack::Instance().pop(true);
    Stack::Instance().push( command_(next_, top_) );

    return;
}

void BinaryCommandAlternative::undoImpl() noexcept
{
    // suppress change signal so only one event raised for the execute
    Stack::Instance().pop(true);
    Stack::Instance().push(next_, true);
    Stack::Instance().push(top_);

    return;
}



}

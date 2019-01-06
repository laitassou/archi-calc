
#ifndef COMMAND_DISPATCHER_H
#define COMMAND_DISPATCHER_H

#include <string>
#include <memory>
#include "Command.h"
#include <set>

namespace mydesign {

class UserInterface;

class CommandDispatcher
{
    class CommandDispatcherImpl;

public:
    explicit CommandDispatcher(UserInterface& ui);
    ~CommandDispatcher();

    void commandEntered(const std::string& command);

private:
    CommandDispatcher(const CommandDispatcher&) = delete;
    CommandDispatcher(CommandDispatcher&&) = delete;
    CommandDispatcher& operator=(const CommandDispatcher&) = delete;
    CommandDispatcher& operator=(CommandDispatcher&&) = delete;


    std::unique_ptr<CommandDispatcherImpl> pimpl_;
};

}

#endif

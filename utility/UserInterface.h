#pragma once

#include <string>
#include "Publisher.h"

namespace mydesign{

  class CommandData : public EventData
  {
  public:
      CommandData(const std::string& s) : command_(s) { }
      const std::string& command() const { return command_; }

  private:
      std::string command_;
  };

  class UserInterface : protected Publisher
  {
  public:
      UserInterface() { registerEvent(CommandEntered); }
      virtual ~UserInterface() { }

      // post a message to the user
      virtual void postMessage(const std::string& m) = 0;

      // notifies the interface that the stack has changed
      virtual void stackChanged() = 0;

      using Publisher::attach;
      using Publisher::detach;

      // defines the event this publisher can raise
      // note that the string is defined in main.cpp of the application since
      // class UserInterface has no implementation file (in test driver for same
      // reason)
      static const std::string CommandEntered;
  };
}

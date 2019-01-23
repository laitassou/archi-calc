#include "CommandRepository.h"
#include "Command.h"
#include <unordered_map>
#include "utility/Exception.h"
#include <sstream>


using std::string;
using std::unordered_map;
using std::set;

namespace mydesign {

  class CommandRepository::CommandRepositoryImpl
  {
    public:
      CommandRepositoryImpl();
      void registerCommand(const std::string& name, CommandPtr c);

      CommandPtr deregisterCommand(const std::string& name);

      size_t getNumberCommands() const { return repository_.size(); }
      CommandPtr allocateCommand(const std::string& name) const;

      bool hasKey(const std::string& s) const;

      std::set<std::string> getAllCommandNames() const;

      void printHelp(const std::string& command, std::ostream& os);
      void clearAllCommands();


    private:
      using Repository = unordered_map<string, CommandPtr>;
      Repository repository_;
  };

  CommandRepository::CommandRepositoryImpl::CommandRepositoryImpl()
  {
  }


  bool CommandRepository::CommandRepositoryImpl::hasKey(const string& s) const
  {
      return repository_.find(s) != repository_.end();
  }


  set<string> CommandRepository::CommandRepositoryImpl::getAllCommandNames() const
  {
      set<string> tmp;

      for(auto i = repository_.begin(); i != repository_.end(); ++i)
          tmp.insert(i->first);

      return tmp;
  }

  void CommandRepository::CommandRepositoryImpl::printHelp(const std::string& command, std::ostream& os)
  {
      auto it = repository_.find(command);
      if(it != repository_.end())
          os << command << ": " << it->second->helpMessage();
      else
          os << command << ": no help entry found";

      return;
  }

  void CommandRepository::CommandRepositoryImpl::clearAllCommands()
  {
      repository_.clear();
      return;
  }
  void CommandRepository::CommandRepositoryImpl::registerCommand(const std::string& name, CommandPtr c)
  {
    if(hasKey(name))
    {
      std::ostringstream oss;
      oss << "Command " << name << " already registered";
      throw Exception{ oss.str() };
    }
    else{
      repository_.emplace(name,std::move(c));
    }

  }
  CommandPtr CommandRepository::CommandRepositoryImpl::deregisterCommand(const string& name)
  {
      if( hasKey(name) )
      {
          auto i = repository_.find(name);
          auto tmp = MakeCommandPtr( i->second.release() );
          repository_.erase(i);
          return tmp;
      }
      else return MakeCommandPtr(nullptr);
  }

  CommandPtr CommandRepository::CommandRepositoryImpl::allocateCommand(const string &name) const
  {
      if( hasKey(name) )
      {
          const auto& command = repository_.find(name)->second;
          return MakeCommandPtr( command->clone() );
      }
      else return MakeCommandPtr(nullptr);
  }

  CommandRepository::CommandRepository()
  : pimpl_{ new CommandRepositoryImpl }
  {
  }

  CommandRepository::~CommandRepository()
  { }

  CommandRepository & CommandRepository::Instance()
  {
    static CommandRepository instance;
    return instance;
  }

  void CommandRepository::registerCommand(const std::string& name, CommandPtr c)
  {
    pimpl_->registerCommand(name,std::move(c));
    return;
  }

  CommandPtr CommandRepository::deregisterCommand(const std::string& name)
  {
    return pimpl_->deregisterCommand(name);
  }
  size_t CommandRepository::getNumberCommands() const
  {
      return pimpl_->getNumberCommands();
  }

  CommandPtr CommandRepository::allocateCommand(const string& name) const
  {
      return pimpl_->allocateCommand(name);
  }

  bool CommandRepository::hasKey(const string& s) const
  {
      return pimpl_->hasKey(s);
  }

  set<string> CommandRepository::getAllCommandNames() const
  {
      return pimpl_->getAllCommandNames();
  }

  void CommandRepository::printHelp(const std::string& command, std::ostream& os) const
  {
      pimpl_->printHelp(command, os);
      return;
  }

  void CommandRepository::clearAllCommands()
  {
      pimpl_->clearAllCommands();
      return;
  }
}

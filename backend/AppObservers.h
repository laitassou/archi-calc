#ifndef APP_OBSERVERS_H
#define APP_OBSERVERS_H

#include "utility/Observer.h"
#include "CommandDispatcher.h"

namespace mydesign {

class UserInterface;

class CommandIssuedObserver : public Observer
{
public:
    explicit CommandIssuedObserver(CommandDispatcher& ce);

private:
    void notifyImpl(std::shared_ptr<EventData>) override;

    CommandDispatcher& ce_;
};

class StackUpdatedObserver : public Observer
{
public:
    explicit StackUpdatedObserver(UserInterface& ui);

private:
    void notifyImpl(std::shared_ptr<EventData>) override;

    UserInterface& ui_;
};


}
#endif

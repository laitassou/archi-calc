
#include "AppObservers.h"
#include "utility/Exception.h"
#include "ui/Cli.h"
#include "Stack.h"
#include "utility/UserInterface.h"
#include <vector>
#include <sstream>

using std::ostringstream;
using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::vector;

namespace mydesign {

CommandIssuedObserver::CommandIssuedObserver(CommandDispatcher& ce)
: Observer("CommandIssued")
, ce_(ce)
{ }

void CommandIssuedObserver::notifyImpl(std::shared_ptr<EventData> eventData)
{
    auto data = dynamic_pointer_cast<CommandData>(eventData);
    if(!data)
    {
        throw Exception("Could not convert CommandData to a command");
    }
    else
    {
        ce_.commandEntered( data->command() );
    }

    return;
}

StackUpdatedObserver::StackUpdatedObserver(UserInterface& ui)
: Observer("StackUpdated")
, ui_(ui)
{ }

void StackUpdatedObserver::notifyImpl(std::shared_ptr<EventData>)
{
    ui_.stackChanged();

    return;
}

}

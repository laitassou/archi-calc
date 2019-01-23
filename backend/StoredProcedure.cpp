#include "StoredProcedure.h"
#include "CommandDispatcher.h"
#include "utility/Exception.h"
#include "utility/Tokenizer.h"
#include <fstream>

using std::string;

namespace mydesign {

StoredProcedure::StoredProcedure(UserInterface& ui, const string& filename)
: filename_{filename}
{
    ce_ = std::make_unique<CommandDispatcher>(ui);
}

StoredProcedure::~StoredProcedure()
{ }

void StoredProcedure::checkPreconditionsImpl() const
{
    if(first_)
    {
        try
        {
            std::ifstream ifs{ filename_.c_str() };
            if(!ifs)
                throw Exception{"Could not open procedure"};

            tokenizer_ = std::make_unique<Tokenizer>(ifs);
        }
        catch(...)
        {
            throw Exception{"Could not open procedure"};
        }
    }

    return;
}

void StoredProcedure::executeImpl() noexcept
{
    if(first_)
    {
        for(auto c : *tokenizer_)
        {
            ce_->commandEntered(c);
        }
        first_ = false;
    }
    else
    {
        for(unsigned int i = 0; i < tokenizer_->nTokens(); ++i)
            ce_->commandEntered("redo");
    }

    return;
}

void StoredProcedure::undoImpl() noexcept
{
    for(unsigned int i = 0; i < tokenizer_->nTokens(); ++i)
        ce_->commandEntered("undo");

    return;
}

Command*StoredProcedure::cloneImpl() const noexcept
{
    return 0;
}

const char* StoredProcedure::helpMessageImpl() const noexcept
{
    return "Executes a stored procedure from disk";
}

}

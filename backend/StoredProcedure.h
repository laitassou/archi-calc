#ifndef STORED_PROCEDURE_H
#define STORED_PROCEDURE_H

#include "Command.h"
#include "utility/Tokenizer.h"
#include <string>
#include <memory>

namespace mydesign {

class CommandDispatcher;
class UserInterface;

class StoredProcedure : public Command
{
public:
    StoredProcedure(UserInterface& ui, const std::string& filename);
    ~StoredProcedure();

private:
    StoredProcedure() = delete;
    StoredProcedure(StoredProcedure&&) = delete;
    StoredProcedure& operator=(const StoredProcedure&) = delete;
    StoredProcedure& operator=(StoredProcedure&&) = delete;
    StoredProcedure(const StoredProcedure&) = delete;

    void checkPreconditionsImpl() const override;
    void executeImpl() noexcept override;
    void undoImpl() noexcept override;
    Command* cloneImpl() const noexcept override;
    const char* helpMessageImpl() const noexcept override;

    mutable std::unique_ptr<Tokenizer> tokenizer_;
    std::unique_ptr<CommandDispatcher> ce_;
    std::string filename_;
    bool first_ = true;
};

}

#endif

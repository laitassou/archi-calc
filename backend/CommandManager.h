#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include <memory>
#include "Command.h"

namespace mydesign {

class CommandManager
{
    class CommandManagerImpl;
    class UndoRedoStackStrategy;
    class UndoRedoListStrategyVector;
    class UndoRedoListStrategy;
public:
    enum class UndoRedoStrategy { ListStrategy, StackStrategy, ListStrategyVector };

    explicit CommandManager(UndoRedoStrategy st = UndoRedoStrategy::StackStrategy);
    ~CommandManager();

    size_t getUndoSize() const;
    size_t getRedoSize() const;

    // This function call executes the command, enters the new command onto the undo stack,
    // and it clears the redo stack. This is consistent with typical undo/redo functionality.
    void executeCommand(CommandPtr c);

    // This function undoes the command at the top of the undo stack and moves this command
    // to the redo stack. It does nothing if the undo stack is empty.
    void undo();

    // This function executes the command at the top of the redo stack and moves this command
    // to the undo stack. It does nothing if the redo stack is empty.
    void redo();

private:
    CommandManager(CommandManager&) = delete;
    CommandManager(CommandManager&& ) = delete;
    CommandManager& operator=(CommandManager&) = delete;
    CommandManager& operator=(CommandManager&&) = delete;

    std::unique_ptr<CommandManagerImpl> pimpl_;
};

}

#endif

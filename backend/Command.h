#pragma once


#include <string>
#include <memory>

#include <functional>



namespace mydesign {

 class Command
 {
    public:
         virtual ~ Command() {};
      	 void execute();
      	 void undo();
      	 Command * clone () const;
      	 const char * helpMessage() const;
      	 virtual void deallocate();

    protected:
          Command() {};
	        Command (const Command&) {};
    private:
         virtual void checkPreconditionsImpl() const;
      	 virtual void executeImpl() noexcept = 0;
      	 virtual void undoImpl() noexcept = 0;
      	 virtual Command* cloneImpl() const = 0;

	 virtual const char * helpMessageImpl() const noexcept = 0;

	 Command(Command&&) = delete;
	 Command & operator = (const Command &) = delete;
	 Command & operator = (Command &&) = delete;
 };





// Base class for binary operations: take two elements from stack and return
// one result. For any binary operation x and stack with top and next,
// the binary operation is applied as next x top
// Precondition: Binary operations must have at least two elements
// on the stack
// The reason to have a binary operations class is because undo,
// redo, and preconditions can be implemented identically
class BinaryCommand : public Command
{
public:
    virtual ~BinaryCommand();

protected:
    // throws an exception if the stack size is less than two
    void checkPreconditionsImpl() const override;

    BinaryCommand() { };
    BinaryCommand(const BinaryCommand&);

private:
    BinaryCommand(BinaryCommand&&) = delete;
    BinaryCommand& operator=(const BinaryCommand&) = delete;
    BinaryCommand& operator=(BinaryCommand&&) = delete;

    // takes two elements from the stack, applies the binary operation
    // and returns the result to the stack
    void executeImpl() noexcept override;

    // drops the result and returns the original two numbers to the stack
    void undoImpl() noexcept override;

    virtual double binaryOperation(double next, double top) const noexcept = 0;

    double top_;
    double next_;
};

// Base class for unary operations: take one element from the stack and return
// one result.
// Precondition: Unary operations must have at least one element on the stack.
// The reason to have a unary operations class is to avoid repetition for
// all classes implementing a unary interface.
class UnaryCommand : public Command
{
public:
    virtual ~UnaryCommand();

protected:
    // throws an exception if the stack size is less than one
    void checkPreconditionsImpl() const override;

    UnaryCommand() { }
    UnaryCommand(const UnaryCommand&);

private:
    UnaryCommand(UnaryCommand&&) = delete;
    UnaryCommand& operator=(const UnaryCommand&) = delete;
    UnaryCommand& operator=(UnaryCommand&&) = delete;

    // takes one element from the stack, applies the binary operation
    // and returns the result to teh stack
    void executeImpl() noexcept override;

    // drops the result and returns the original number to the stack
    void undoImpl() noexcept override;

    virtual double unaryOperation(double top) const noexcept = 0;

    double top_;
};

class PluginCommand : public Command
{
public:
    virtual ~PluginCommand();

private:
    virtual const char* checkPluginPreconditions() const noexcept = 0;
    virtual PluginCommand* clonePluginImpl() const noexcept = 0;

    void checkPreconditionsImpl() const override final;
    PluginCommand* cloneImpl() const override final;
};

// This shows an entirely different design using function and lambdas.
class BinaryCommandAlternative final : public Command
{
    using BinaryCommandOp = double(double, double);
public:
    BinaryCommandAlternative(const std::string& help, std::function<BinaryCommandOp> f);
    ~BinaryCommandAlternative() = default;

private:
    BinaryCommandAlternative(BinaryCommandAlternative&&) = delete;
    BinaryCommandAlternative& operator=(const BinaryCommandAlternative&) = delete;
    BinaryCommandAlternative& operator=(BinaryCommandAlternative&&) = delete;

    // throws an exception if the stack size is less than two
    void checkPreconditionsImpl() const override;

    BinaryCommandAlternative(const BinaryCommandAlternative&);

    const char* helpMessageImpl() const noexcept override;

    // takes two elements from the stack, applies the binary operation
    // and returns the result to the stack
    void executeImpl() noexcept override;

    // drops the result and returns the original two numbers to the stack
    void undoImpl() noexcept override;

    BinaryCommandAlternative* cloneImpl() const override;

    double top_;
    double next_;
    std::string helpMsg_;
    std::function<BinaryCommandOp> command_;
};

inline void CommandDeleter(Command* p)
{
    p->deallocate();
    return;
}

using CommandPtr = std::unique_ptr<Command, decltype(&CommandDeleter)>;

template<typename T, typename... Args>
auto MakeCommandPtr(Args&&... args)
{
    return CommandPtr{new T{std::forward<Args>(args)...}, &CommandDeleter};
}

inline auto MakeCommandPtr(Command* p)
{
    return CommandPtr{p, &CommandDeleter};
}
}

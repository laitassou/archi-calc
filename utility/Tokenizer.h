#pragma once

#include <string>
#include <vector>
#include <istream>

namespace mydesign {

class  Tokenizer
{
public:
    using Token = std::string;
    using Tokens = std::vector<Token>;
    using const_iterator =  Tokens::const_iterator;

    explicit Tokenizer(const std::string&);
    explicit Tokenizer(std::istream&);
    ~Tokenizer();

    size_t nTokens() const { return tokens_.size(); }

    const_iterator begin() const { return tokens_.begin(); }
    const_iterator end() const { return tokens_.end(); }

    const Token& operator[](size_t i) const { return tokens_[i]; }

private:
    void tokenize(std::istream&);

    Tokenizer() = delete;
    Tokenizer(const Tokenizer&) = delete;
    Tokenizer(Tokenizer&&) = delete;
    Tokenizer& operator=(const Tokenizer&) = delete;
    Tokenizer& operator=(Tokenizer&&) = delete;

    Tokens tokens_;
};

}

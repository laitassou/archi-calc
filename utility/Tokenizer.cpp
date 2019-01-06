
#include "Tokenizer.h"
#include <sstream>
#include <iterator>
#include <algorithm>

using std::string;
using std::istringstream;
using std::istream_iterator;

namespace mydesign {

Tokenizer::Tokenizer(const string& s)
{
    istringstream iss{s};

    tokenize(iss);
}

Tokenizer::Tokenizer(std::istream& is)
{
    tokenize(is);
}


Tokenizer::~Tokenizer()
{ }

void Tokenizer::tokenize(std::istream& is)
{
    tokens_.assign( istream_iterator<string>{is}, istream_iterator<string>{});

    for(auto& i : tokens_)
        std::transform(i.begin(), i.end(), i.begin(), ::tolower);
}

}

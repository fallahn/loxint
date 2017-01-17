/*
Lox Interpreter from Robert Nystrom's Crafting Interpreters

This is a C++ equivalent of the first (java) version.

This code is released in to the public domain in the hopes that
it may be useful, but with absolutely no warranty.

*/

#ifndef SCANNER_HPP_
#define SCANNER_HPP_

#include "Token.hpp"

#include <vector>
#include <string>

class Scanner final
{
public:
    explicit Scanner(const std::string&);
    ~Scanner() = default;

    const std::vector<Token>& scanTokens();

private:
    std::string m_source;
    int m_currentLine;
    std::size_t m_startPos;
    std::size_t m_currentPos;
    std::vector<Token> m_tokens;

    void scan();
    bool atEnd();
};

#endif //SCANNER_HPP_
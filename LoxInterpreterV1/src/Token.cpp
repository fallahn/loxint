/*
Lox Interpreter from Robert Nystrom's Crafting Interpreters

This is a C++ equivalent of the first (java) version.

This code is released in to the public domain in the hopes that
it may be useful, but with absolutely no warranty.

*/

#include "Token.hpp"

namespace
{
    const std::string typeNames[] = 
    {
        "ParenLeft", "ParenRight", "BraceLeft", "BraceRight",
        "Comma", "Dot", "Minus", "Plus", "SemiColon", "Slash", "Star",

        "Bang", "BangEqual",
        "Equal", "EqualEqual",
        "Greater", "GreaterEqual",
        "Less", "LessEqual",

        "Identifier", "String", "Number",

        "And", "Class", "Else", "False", "Fun", "For", "If", "Nil", "Or",
        "Print", "Return", "Super", "This", "True", "Var", "While",

        "EndOfFile"
    };
}

Token::Token(Token::Type type, const std::string& lexeme, int line)
    : m_type        (type),
    m_lexeme        (lexeme),
    m_line          (line),
    m_numberValue   (0.f)
{

}

Token::Token(Token::Type type, const std::string& lexeme, int line, const std::string& value)
    : m_type        (type),
    m_lexeme        (lexeme),
    m_line          (line),
    m_stringValue   (value),
    m_numberValue   (0.f){}

Token::Token(Token::Type type, const std::string& lexeme, int line, double value)
    : m_type        (type),
    m_lexeme        (lexeme),
    m_line          (line),
    m_stringValue   (),
    m_numberValue   (value) {}

//public
std::string Token::toString() const
{
    std::string v = (m_type == Token::Type::String) ? m_stringValue : std::to_string(m_numberValue);
    return typeNames[(int)m_type] + ": " + m_lexeme + ", " + v;
}
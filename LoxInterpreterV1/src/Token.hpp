/*
Lox Interpreter from Robert Nystrom's Crafting Interpreters

This is a C++ equivalent of the first (java) version.

This code is released in to the public domain in the hopes that
it may be useful, but with absolutely no warranty.

*/

#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <string>

class Token final
{
public:
    enum class Type
    {
        ParenLeft, ParenRight, BraceLeft, BraceRight,
        Comma, Dot, Minus, Plus, SemiColon, Slash, Star,

        Bang, BangEqual,
        Equal, EqualEqual,
        Greater, GreaterEqual,
        Less, LessEqual,

        Identifier, String, Number,

        And, Class, Else, False, Fun, For, If, Nil, Or,
        Print, Return, Super, This, True, Var, While,

        EndOfFile
    };

    Token(Type, const std::string&, int);
    Token(Type, const std::string&, int, const std::string&);
    Token(Type, const std::string&, int, double);
    ~Token() = default;

    std::string toString() const;

private:
    Type m_type;
    std::string m_lexeme;
    int m_line;

    std::string m_stringValue;
    double m_numberValue;
};

#endif //TOKEN_HPP_
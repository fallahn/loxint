/*
Lox Interpreter from Robert Nystrom's Crafting Interpreters

This is a C++ equivalent of the first (java) version.

This code is released in to the public domain in the hopes that
it may be useful, but with absolutely no warranty.

*/

#include "Scanner.hpp"
#include "LoxInt.hpp"

#include <functional>
#include <unordered_map>

namespace
{
    const std::unordered_map<std::string, Token::Type> reservedWords = 
    {
        std::make_pair("and", Token::Type::And),
        std::make_pair("class", Token::Type::Class),
        std::make_pair("else", Token::Type::Else),
        std::make_pair("false", Token::Type::False),
        std::make_pair("fun", Token::Type::Fun),
        std::make_pair("if", Token::Type::If),
        std::make_pair("nil", Token::Type::Nil),
        std::make_pair("or", Token::Type::Or),
        std::make_pair("print", Token::Type::Print),
        std::make_pair("return", Token::Type::Return),
        std::make_pair("super", Token::Type::Super),
        std::make_pair("this", Token::Type::This),
        std::make_pair("var", Token::Type::Var),
        std::make_pair("while", Token::Type::While)
    };
}

Scanner::Scanner(const std::string& src)
    : m_source      (src),
    m_currentLine   (0),
    m_startPos      (0),
    m_currentPos    (0)
{

}

//public
const std::vector<Token>& Scanner::scanTokens()
{
    while (!atEnd())
    {
        m_startPos = m_currentPos;
        scan();
    }
    
    m_tokens.emplace_back(Token::Type::EndOfFile, "", m_currentLine);
    return m_tokens;
}

//private
void Scanner::scan()
{
    //----helper functions----//
    auto advance = [this]()->char
    {
        return m_source[m_currentPos++];
    };

    auto addToken = [this](Token::Type type)
    {
        m_tokens.emplace_back(type, m_source.substr(m_startPos, m_currentPos), m_currentLine);
    };

    auto match = [this](char c)->bool
    {
        if (atEnd()) return false;
        if (m_source[m_currentPos] != c) return false;
        m_currentPos++;
        return true;
    };

    auto peek = [this]()->char
    {
        return m_source[m_currentPos];
    };

    auto peekNext = [this]()->char
    {
        if (m_currentPos + 1 >= m_source.size()) return '\0';
        return m_source[m_currentPos + 1];
    };

    auto string = [&, this]()
    {
        while (peek() != '"' && !atEnd())
        {
            if (peek() == '\n')
            {
                m_currentLine++;
            }
            advance();
        }

        if (atEnd())
        {
            Lox::printError(m_currentLine, "Unterminated string");
            return;
        }

        advance();
        std::string value = m_source.substr(m_startPos + 1, m_currentPos - 1);
        m_tokens.emplace_back(Token::Type::String, m_source.substr(m_startPos, m_currentPos), m_currentLine, value);
    };

    auto isDigit = [](char c)->bool
    {
        return (c >= '0' && c <= '9');
    };

    auto number = [&, this]()
    {
        while (isDigit(peek()))
        {
            advance();
        }

        if (peek() == '.' && isDigit(peekNext()))
        {
            advance();
            while (isDigit(peek()))
            {
                advance();
            }
        }

        try
        {
            double value = std::stod(m_source.substr(m_startPos, m_currentPos).c_str());
            m_tokens.emplace_back(Token::Type::Number, m_source.substr(m_startPos, m_currentPos), m_currentLine, value);
        }
        catch (...)
        {
            Lox::printError(m_currentLine, "Failed parsing numeric value");
        }
    };

    auto isAlpha = [](char c) ->bool
    {
        return (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '_';
    };

    auto isAlphaNumeric = [&](char c)->bool
    {
        return isAlpha(c) || isDigit(c);
    };

    auto identifier = [&, this]()
    {
        while (isAlphaNumeric(peek())) advance();

        auto text = m_source.substr(m_startPos, m_currentPos);
        if (reservedWords.count(text) > 0)
        {
            addToken(reservedWords.find(text)->second);
            return;
        }

        addToken(Token::Type::Identifier);
    };

    //---end of helpers---//

    auto c = advance();
    switch (c)
    {
    default: 
        if(isDigit(c))
        {
            number();
        }
        else if (isAlpha(c))
        {
            identifier();
        }
        else
        {
            Lox::printError(m_currentLine, std::string(1, c) + ": Unexpected character");
        }
        break;
    case '(':
        addToken(Token::Type::ParenLeft);
        break;
    case ')':
        addToken(Token::Type::ParenRight);
        break;
    case '{':
        addToken(Token::Type::BraceLeft);
        break;
    case '}':
        addToken(Token::Type::BraceRight);
        break;
    case ',':
        addToken(Token::Type::Comma);
        break;
    case '.':
        addToken(Token::Type::Dot);
        break;
    case '-':
        addToken(Token::Type::Minus);
        break;
    case '+':
        addToken(Token::Type::Plus);
        break;
    case ';':
        addToken(Token::Type::SemiColon);
        break;
    case '*':
        addToken(Token::Type::Star);
        break;

    case '!':
        addToken(match('=') ? Token::Type::BangEqual : Token::Type::Bang);
        break;
    case '=':
        addToken(match('=') ? Token::Type::EqualEqual : Token::Type::Equal);
        break;
    case '<':
        addToken(match('=') ? Token::Type::LessEqual : Token::Type::Less);
        break;
    case '>':
        addToken(match('=') ? Token::Type::GreaterEqual : Token::Type::Greater);
        break;
    case '/':
    {
        //handle comments
        if (match('/'))
        {
            while (peek() != '\n' && !atEnd())
            {
                advance();
            }
        }
        else
        {
            addToken(Token::Type::Slash);
        }
    }
    break;


    //whitespace
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        m_currentLine++;
        break;

    //string literals
    case '"':
        string();
        break;
    }
}

bool Scanner::atEnd()
{
    return !(m_currentPos < m_source.size());
}
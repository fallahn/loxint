/*
Lox Interpreter from Robert Nystrom's Crafting Interpreters

This is a C++ equivalent of the first (java) version.

This code is released in to the public domain in the hopes that
it may be useful, but with absolutely no warranty.

*/

#ifndef LOXINT_HPP_
#define LOXINT_HPP_

#include <string>

class Lox final
{
public:
    Lox();
    ~Lox() = default;

    void runFile(const char*);
    void runPrompt();

    static void printError(int line, const std::string& msg);

private:
    void run(const std::string&);

    static void log(int line, const std::string& where, const std::string& message);
};

#endif //LOXINT_HPP_
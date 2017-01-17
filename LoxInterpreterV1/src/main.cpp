/*
Lox Interpreter from Robert Nystrom's Crafting Interpreters

This is a C++ equivalent of the first (java) version.

This code is released in to the public domain in the hopes that
it may be useful, but with absolutely no warranty.

*/

#include "LoxInt.hpp"

#include <iostream>

int main(int argc, char** argsv)
{
    Lox lox;
    
    if (argc == 2)
    {
        lox.runFile(argsv[1]);
    }
    else
    {
        lox.runPrompt();
    }

    return 0;
}
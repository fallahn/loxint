/*
Lox Interpreter from Robert Nystrom's Crafting Interpreters

This is a C++ equivalent of the first (java) version.

This code is released in to the public domain in the hopes that
it may be useful, but with absolutely no warranty.

*/

#include "LoxInt.hpp"
#include "Scanner.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace
{
    bool hadError = false;
}

Lox::Lox()
{

}

//public
void Lox::runFile(const char* path) 
{
    std::ifstream file(path);
    if (file.is_open() && file.good())
    {
        //read in entire script to single stream
        //TODO in *theory* REALLY large files could break everything
        std::string str(static_cast<std::stringstream const&>(std::stringstream() << file.rdbuf()).str());
        run(str);
        if (hadError) exit(65);
    }
    else
    {
        std::cout << "Failed to open: " << path << std::endl;
    }
}

void Lox::runPrompt()
{
    std::cout << "Hello! Welcome to LoxInt V1\n" << "---------------------------" << std::endl;
    std::cout << "Enter command or \'quit\' to exit" << std::endl;

    std::string input;
    while (1) //TODO how do we break this? Ctrl-C I guess
    {
        std::cout << ">";
        std::getline(std::cin, input);

        if (input == "quit") return;

        run(input);
        hadError = false;
    }
}

void Lox::printError(int line, const std::string& msg)
{
    log(line, "", msg);
}

//private
void Lox::run(const std::string& str)
{
    Scanner scanner(str);
    const auto tokens = scanner.scanTokens();

    for (const auto& t : tokens)
    {
        std::cout << t.toString() << std::endl;
    }
}

void Lox::log(int line, const std::string& position, const std::string& message)
{
    std::cout << "[line " << line << "] Error " << position << ": " << message <<std::endl;
    //TODO make this output more useful information
}
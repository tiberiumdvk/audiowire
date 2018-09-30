#pragma once
#include <string>
#include <map>

struct arguments
{
    arguments(int argc, char** argv);
    std::string command;
    std::string object;
    std::map<std::string, std::string> flags;
};
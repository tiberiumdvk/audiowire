#pragma once
#include <string>
#include <map>

struct arguments
{
    arguments(int argc, char** argv);
    
    std::string command;
    std::map<std::string, std::string> flags;

    bool has_flag(const std::string& flag);
};
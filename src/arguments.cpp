#include "arguments.hpp"

arguments::arguments(int argc, char** argv)
{
    command = argv[1];

    char* current_flag = nullptr;

    for (int i = 2; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            current_flag = argv[i];
            flags[current_flag] = "";
        }
        else if (current_flag != nullptr)
        {
            // add whitespace after consecutive arguments to allow passing spaced input without brackets
            if (!flags[current_flag].empty())
            {
                flags[current_flag].push_back(' ');
            }

            flags[current_flag] += argv[i];
        }
    }
}

bool arguments::has_flag(const std::string& flag)
{
    return this->flags.count(flag) > 0;
}
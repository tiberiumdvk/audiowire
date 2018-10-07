#pragma once
#include "song.hpp"
#include <vector>

namespace audiowire
{

struct song_parser
{
    std::string serialize(std::vector<audiowire::song>& song_list);
    std::vector<audiowire::song> deserialize(const std::string& serialized_data);
};

}
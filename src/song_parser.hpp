#pragma once
#include "song.hpp"
#include <list>

namespace audiowire
{

struct song_parser
{
    std::string serialize(std::list<audiowire::song>& song_list);
    std::list<audiowire::song> deserialize(const std::string& serialized_data);
};

}
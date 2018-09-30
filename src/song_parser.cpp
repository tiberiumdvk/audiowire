#include "song_parser.hpp"
#include <sstream>

std::string audiowire::song_parser::serialize(std::list<audiowire::song>& song_list)
{
    std::stringstream sstream;

    for (auto& song : song_list)
    {
        sstream << song.title << ":" << song.artist << ":" << song.album << ";";
    }

    return std::move(sstream.str()); // redundant rval cast ?
}

std::list<audiowire::song> audiowire::song_parser::deserialize(const std::string& serialized_data)
{
    std::list<audiowire::song> song_list;

    audiowire::song current_song;

    int tag = 0;
    
    for (int i = 0; i < serialized_data.length(); i++)
    {
        if (serialized_data[i] == '\n')
            continue;
        
        if (serialized_data[i] == ';')
        {
            song_list.push_back(std::move(current_song));
            current_song = audiowire::song();
            tag = 0;
            continue;
        }

        if (serialized_data[i] == ':')
        {
            if (tag < 3)
            {
                tag++;
            }
            else
            {
                tag = 0;
            }
            
            continue;
        }

        switch (tag)
        {
            case 0:
            {
                current_song.title.push_back(serialized_data[i]);
            }
            break;
            case 1:
            {
                current_song.artist.push_back(serialized_data[i]);
            }
            break;
            case 2:
            {
                current_song.album.push_back(serialized_data[i]);
            }
            break;
        }
    }

    return std::move(song_list);
}

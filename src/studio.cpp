#include "studio.hpp"
#include <sstream>

std::list<const audiowire::song*> audiowire::studio::get_song_list_where(std::function<bool(const audiowire::song&)> predicate)
{
    std::list<const audiowire::song*> selected_song_list;

    for (auto song : _song_list)
    {
        if (predicate(song))
        {
            selected_song_list.push_back(&song);
        }
    }

    return std::move(selected_song_list);
}

bool audiowire::studio::open(const std::string& path)
{
    std::fstream file(path, std::ios::out | std::ios::in | std::ios::app);

    if (!file.is_open() || file.bad())
    {
        return false;
    }

    std::stringstream sstream;
    sstream << file.rdbuf();
    
    file.close();
    
    _song_list = _song_parser.deserialize(sstream.str());   

    return true;
}

bool audiowire::studio::save(const std::string& path)
{
    std::fstream file(path, std::ios::out | std::ios::trunc);

    if (!file.is_open() || file.bad())
    {
        return false;
    }

    std::string serialized_data = _song_parser.serialize(_song_list);
    file.write(serialized_data.c_str(), serialized_data.length());

    file.close();

    return true;
}

const std::list<audiowire::song>& audiowire::studio::get_song_list()
{
    return (const std::list<audiowire::song>&)_song_list;
}

std::list<const audiowire::song*> audiowire::studio::get_song_list_by_artist(const std::string& artist)
{
    return get_song_list_where([&artist](const audiowire::song& song)
    {
        return song.artist == artist;
    });
}

std::list<const audiowire::song*> audiowire::studio::get_song_list_by_album(const std::string& album)
{
    return get_song_list_where([&album](const audiowire::song& song)
    {
        return song.artist == album;
    });
}

void audiowire::studio::add_song(const audiowire::song& new_song)
{
    _song_list.push_back(new_song);
}

void audiowire::studio::remove_song(const std::string& title)
{
    _song_list.remove_if([&title](const audiowire::song& song)
    {
        return song.title == title;
    });
}
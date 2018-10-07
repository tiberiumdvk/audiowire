#include "studio.hpp"
#include <sstream>

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

readonly_list audiowire::studio::get_where(std::function<bool(const audiowire::song&)> predicate)
{
    std::vector<audiowire::song*> matching_songs;
    
    for (auto& song : _song_list)
    {
        if (predicate(song))
        {
            matching_songs.push_back(&song);       
        }
    }

    return std::move(matching_songs);
}

int audiowire::studio::delete_where(std::function<bool(const audiowire::song&)> predicate)
{
    std::vector<audiowire::song> new_songs; // TODO: change "deleting" logic, so it doesn't involve swapping vectors
    
    for (int i = 0; i < _song_list.size(); i++)
    {
        if (!predicate(_song_list[i]))
        {
            new_songs.push_back(_song_list[i]);
        }        
    }

    int count_deleted = _song_list.size() - new_songs.size();

    _song_list.swap(new_songs);

    return count_deleted;
}

void audiowire::studio::edit(std::function<void(audiowire::song&)> predicate) // stupid idea but w/e
{
    for (auto& song : _song_list)
    {
        predicate(song);
    }
}

void audiowire::studio::add(audiowire::song song)
{
    _song_list.push_back(song);
}
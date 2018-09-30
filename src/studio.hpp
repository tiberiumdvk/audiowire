#pragma once
#include <list>
#include <string>
#include <functional>
#include <fstream>
#include "song.hpp"
#include "song_parser.hpp"

#define STUDIO_FILE_PATH "./studio.awproj"

namespace audiowire
{

class studio
{
private:

    audiowire::song_parser _song_parser;

    std::list<audiowire::song> _song_list;

    std::list<const audiowire::song*> get_song_list_where(std::function<bool(const audiowire::song&)> predicate);

public:

    bool open(const std::string& path);
    bool save(const std::string& path);

    const std::list<audiowire::song>& get_song_list();
    std::list<const audiowire::song*> get_song_list_by_artist(const std::string& artist);
    std::list<const audiowire::song*> get_song_list_by_album(const std::string& album);

    void add_song(const audiowire::song& new_song);
    void remove_song(const std::string& title);
};

};
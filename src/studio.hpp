#pragma once
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include "song.hpp"
#include "song_parser.hpp"

#define STUDIO_FILE_PATH "./studio.awproj"

typedef const std::vector<audiowire::song*> readonly_list;

namespace audiowire
{

class studio
{
private:

    audiowire::song_parser _song_parser;

    std::vector<audiowire::song> _song_list;

public:

    bool open(const std::string& path);
    bool save(const std::string& path);

    readonly_list get_where(std::function<bool(const audiowire::song&)> predicate);
    int delete_where(std::function<bool(const audiowire::song&)> predicate);
    void edit(std::function<void(audiowire::song&)> predicate);
    void add(audiowire::song song);
};

};
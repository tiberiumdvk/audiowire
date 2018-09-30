#include <iostream>
#include <experimental/filesystem>
#include "arguments.hpp"
#include "debug.hpp"
#include "studio.hpp"

void _print_indentet(const char* content)
{
    std::cout << "    " << content << std::endl;
}

void print_help()
{
    std::cout << "audiowire [command] [options...]" << std::endl << std::endl;
    std::cout << "commands:" << std::endl;
    _print_indentet("add [object] [options...]");
    _print_indentet("remove [object] [options...]");
    _print_indentet("edit [object] [options...]");
    _print_indentet("list [object] [options...]");
    std::cout << std::endl << "objects:" << std::endl;
    _print_indentet("song [--title title] [--artist artist] [--album album]");
    _print_indentet("album [--title title] [--artist artist] [--songs songs...]");
    _print_indentet("artist [--name name] [--songs songs...] [--albums albums...]");
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {   
        print_help();
        return 0;
    }

    arguments args(argc, argv);

    if (args.command.empty() || args.flags.count("--help") > 0)
    {
        print_help();
        return 0;
    }

    audiowire::studio studio;
    if (!studio.open(STUDIO_FILE_PATH))
    {
        std::cerr << "Error creating or opening file!" << std::endl;            
        return 1;
    }

    if (args.command == "add")
    {
        if (args.object == "song")
        {
            audiowire::song new_song;
            new_song.title = args.flags["--title"];
            new_song.artist = args.flags["--artist"];
            new_song.album = args.flags["--album"];

            studio.add_song(new_song);
        }
        else if (args.object == "artist")
        {
            
        }
        else if (args.object == "album")
        {
            
        }
        
        if (!studio.save(STUDIO_FILE_PATH))
        {
            std::cerr << "Error creating or opening file!" << std::endl;
        }

        return 0;
    }

    if (args.command == "remove")
    {
        
        
        return 0;
    }

    if (args.command == "edit")
    {
        
        
        return 0;
    }

    if (args.command == "list")
    {
        if (args.object == "song")
        {
            auto& song_list = studio.get_song_list();
            for (auto& song : song_list)
            {
                std::cout << "title:" << song.title << '\n' 
                << "artist:" << song.artist << '\n' 
                << "album:" << song.album 
                << '\n' 
                << std::endl;
            }
        }
           
        return 0;
    }

    print_help();
}
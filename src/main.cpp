#include <iostream>
#include "cli.hpp"
#include "arguments.hpp"
#include "debug.hpp"
#include "studio.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        print_help();
        return 0;
    }

    arguments args(argc, argv);

    if (args.has_flag("--help") || args.flags.size() == 0)
    {
        print_command_help(args.command);
        return 0;
    }

    audiowire::studio studio;

    if (!studio.open(STUDIO_FILE_PATH))
    {
        std::cerr << "Error creating or opening file!" << std::endl;
        return 1;
    }

    // COMMANDS
    #pragma region LIST

    if (args.command == "list")
    {
        std::vector<audiowire::song*> songs;

        if (args.has_flag("--all"))
        {
            songs = studio.get_where([](const audiowire::song& song)
            {
                return true;
            });
        }
        else if (args.has_flag("--title"))
        {
            songs = studio.get_where([&args](const audiowire::song& song)
            {
                return song.title == args.flags["--title"];
            });
        }
        else if (args.has_flag("--artist"))
        {
            songs = studio.get_where([&args](const audiowire::song& song)
            {
                return song.artist == args.flags["--artist"];
            });
        }
        else if (args.has_flag("--album"))
        {
            songs = studio.get_where([&args](const audiowire::song& song)
            {
                return song.album == args.flags["--album"];
            });
        }

        std::cout << "Matching results" << " " << "(" << songs.size() << ")" << std::endl;

        for (auto song : songs)
        {
            std::cout << song->title << " - " << song->artist;

            if (!song->album.empty())
            {
                std::cout << " : " << song->album;
            }

            std::cout << std::endl;
        }

        return 0;
    }

    #pragma endregion

    #pragma region NEW

    if (args.command == "new")
    {
        if (args.has_flag("--title") && args.has_flag("--artist"))
        {
            audiowire::song new_song;
            new_song.title = args.flags["--title"];
            new_song.artist = args.flags["--artist"];
            new_song.album = (args.has_flag("--album"))? args.flags["--album"] : "";

            studio.add(std::move(new_song));
            studio.save(STUDIO_FILE_PATH);

            return 0;
        }
    }

    #pragma endregion

    #pragma region DELETE

    if (args.command == "delete")
    {
        int count_deleted = 0;

        if (args.has_flag("--title"))
        {
            count_deleted = studio.delete_where([&args](const audiowire::song& song)
            {
                return song.title == args.flags["--title"];
            });
        }
        else if (args.has_flag("--artist"))
        {
            count_deleted = studio.delete_where([&args](const audiowire::song& song)
            {
                return song.artist == args.flags["--artist"];
            });
        }
        else if (args.has_flag("--album"))
        {
            count_deleted = studio.delete_where([&args](const audiowire::song& song)
            {
                return song.album == args.flags["--album"];
            });
        }

        else if (args.has_flag("--all"))
        {
            count_deleted = studio.delete_where([&args](const audiowire::song& song)
            {
                return true;
            });
        }

        std::cout << "Deleted songs" << " " << "(" << count_deleted << ")" << std::endl;

        if (count_deleted > 0)
        {
            studio.save(STUDIO_FILE_PATH);
            return 0;
        }
    }

    #pragma endregion

    #pragma region EDIT

    if (args.command == "edit")
    {
        if (args.has_flag("--title"))
        {
            studio.edit([&args](audiowire::song& song)
            {
                if (song.title == args.flags["--title"])
                {
                    if (args.has_flag("--new"))
                    {
                        song.title = args.flags["--new"];
                    }

                    if (args.has_flag("--artist"))
                    {
                        song.artist = args.flags["--artist"];
                    }

                    if (args.has_flag("--album"))
                    {
                        song.album = args.flags["--album"];
                    }
                }
            });

            studio.save(STUDIO_FILE_PATH);

            return 0;
        }
    }

    #pragma endregion

    print_help();
}

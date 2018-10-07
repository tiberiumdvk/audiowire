#pragma once
#include <iostream>
#include <iomanip>

typedef int INDENT;
#define INDENT_S 4
#define INDENT_M 6
#define INDENT_L 8

#define MAX_W 8

static void _print(const std::string& content)
{
    std::cout << content;
}

static void _print_indent(const std::string& content, INDENT indent)
{
    std::cout << std::setw(indent + content.length()) << content << std::string(MAX_W - content.length(), ' ');
}

static void _printl(const std::string& content)
{
    std::cout << content << std::endl;
}

static void _printl_indent(const std::string& content, INDENT indent)
{
    std::cout << std::setw(indent + content.length()) << content << std::endl;
}

void print_help()
{
    _print("usage: "); 
    _printl("audiowire [command] [options...]");
    _printl("");
    _printl("Commands:");
    _print_indent("new", INDENT_S);
    _printl_indent("Creates a new song", INDENT_L);
    _print_indent("delete", INDENT_S);
    _printl_indent("Deletes selected song or song group", INDENT_L);
    _print_indent("edit", INDENT_S);
    _printl_indent("Changes a selected song", INDENT_L);
    _print_indent("list", INDENT_S);
    _printl_indent("Prints matching songs", INDENT_L);
}

void print_command_help(const std::string& command)
{
    if (command == "new")
    {
        _print("usage: ");
        _printl("audiowire new [options...]");
        _printl("");
        _printl("Options:");
        _print_indent("--title", INDENT_S);
        _printl_indent("Sets the title [Required]", INDENT_L);
        _print_indent("--artist", INDENT_S);
        _printl_indent("Sets the author [Required]", INDENT_L);
        _print_indent("--album", INDENT_S);
        _printl_indent("Sets the album [Optional]", INDENT_L);
        
        return;
    }

    if (command == "delete")
    {
        _print("usage: ");
        _printl("audiowire delete [option]");
        _printl("");
        _printl("Options:");
        _print_indent("--title", INDENT_S);
        _printl_indent("Deletes a song of given title", INDENT_L);
        _print_indent("--artist", INDENT_S);
        _printl_indent("Deletes songs of given artist", INDENT_L);
        _print_indent("--album", INDENT_S);
        _printl_indent("Deletes songs in given album", INDENT_L);

        return;
    }
    
    if (command == "edit")
    {
        _print("usage: ");
        _printl("audiowire edit [options...]");
        _printl("");
        _printl("Options:");
        _print_indent("--title", INDENT_S);
        _printl_indent("Title of the song to edit [Required]", INDENT_L);
        _print_indent("--new", INDENT_S);
        _printl_indent("Changes the title [Optional]", INDENT_L);
        _print_indent("--artist", INDENT_S);
        _printl_indent("Changes the artist [Optional]", INDENT_L);
        _print_indent("--album", INDENT_S);
        _printl_indent("Changes the album [Optional]", INDENT_L);

        return;
    }
    
    if (command == "list")
    {
        _print("usage: ");
        _printl("audiowire list [option]");
        _printl("");
        _printl("Options:");
        _print_indent("--all", INDENT_S);
        _printl_indent("Shows all songs", INDENT_L);
        _print_indent("--title", INDENT_S);
        _printl_indent("Title of the song to show [Optional]", INDENT_L);
        _print_indent("--artist", INDENT_S);
        _printl_indent("Shows all songs of a artist [Optional]", INDENT_L);
        _print_indent("--album", INDENT_S);
        _printl_indent("Shows all songs in an album [Optional]", INDENT_L);

        return;
    }

    print_help();
}
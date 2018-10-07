#pragma once

#ifdef DEBUG
#include <iostream>
#define LOG(msg) std::clog << msg << std::endl
#define ERR(msg) std::cerr << msg << std::endl
#else
#define LOG(msg)
#define ERR(msg)
#endif
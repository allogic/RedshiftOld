#ifndef RSH_DEBUG_H
#define RSH_DEBUG_H

#include <iostream>
#include <format>

#define RSH_LOG(FMT, ...) std::cout << std::format(FMT, __VA_ARGS__)

#endif
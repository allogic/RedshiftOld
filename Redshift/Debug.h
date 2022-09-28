#ifndef RSH_DEBUG_H
#define RSH_DEBUG_H

#include <cstdio>

#define RSH_LOG(FMT, ...) std::printf(FMT, __VA_ARGS__)

#endif
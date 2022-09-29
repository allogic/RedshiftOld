#ifndef RSH_DEBUG_H
#define RSH_DEBUG_H

#include <cstdio>

#include <Redshift/Platform.h>

#if defined(OS_WINDOWS)
  #define RSH_LOG(FMT, ...) std::printf(FMT, __VA_ARGS__)
#elif defined(OS_LINUX)
  #define RSH_LOG(FMT, ...) std::printf(FMT __VA_OPT__(,) __VA_ARGS__)
#else
  #error "Platform not supported!"
#endif

#endif
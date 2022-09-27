#ifndef RSH_PLATFORM_H
#define RSH_PLATFORM_H

#if defined(_WIN32) || defined(WIN32)
  #define OS_WINDOWS
#elif defined(__unix__)
  #define OS_UNIX
#endif

#endif
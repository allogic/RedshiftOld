#ifndef RSH_PLATFORM_H
#define RSH_PLATFORM_H

#if defined(_WIN32) || defined(WIN32)
  #define OS_WINDOWS
#elif defined(__linux__)
  #define OS_LINUX
#endif

#if defined(OS_WINDOWS)
  #include <filesystem>
#elif defined(OS_LINUX)
  #include <experimental/filesystem>
  namespace std
  {
    namespace filesystem = experimental::filesystem;
  }
#else
  #error "Platform not supported!"
#endif

#endif
#pragma once
#ifndef INC_SINGLETON_API_H_
#define INC_SINGLETON_API_H_

#if defined(_WIN32) || defined(__CYGWIN__)
#  if defined(singleton_EXPORTS) // add by CMake 
#    ifdef __GNUC__
#      define  SINGLETON_API __attribute__(dllexport)
#    else
#      define  SINGLETON_API __declspec(dllexport)
#    endif
#  else
#    ifdef __GNUC__
#      define  SINGLETON_API __attribute__(dllimport)
#    else
#      define  SINGLETON_API __declspec(dllimport)
#    endif
#  endif // singleton_EXPORTS

#elif defined __GNUC__
#  if __GNUC__ >= 4
#    define SINGLETON_API __attribute__ ((visibility ("default")))
#  else
#    define SINGLETON_API
#  endif

#elif defined __clang__
#  define SINGLETON_API __attribute__ ((visibility ("default")))

#else
#   error "Do not know how to export classes for this platform"
#endif

#endif

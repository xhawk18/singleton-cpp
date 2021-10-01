#pragma once
#ifndef INC_MY_DLL_API_H_
#define INC_MY_DLL_API_H_

#if defined(_WIN32) || defined(__CYGWIN__)
#  if defined(my_dll_EXPORTS) // add by CMake 
#    ifdef __GNUC__
#      define  MY_DLL_API __attribute__(dllexport)
#    else
#      define  MY_DLL_API __declspec(dllexport)
#    endif
#  else
#    ifdef __GNUC__
#      define  MY_DLL_API __attribute__(dllimport)
#    else
#      define  MY_DLL_API __declspec(dllimport)
#    endif
#  endif // my_dll_EXPORTS

#elif defined __GNUC__
#  if __GNUC__ >= 4
#    define MY_DLL_API __attribute__ ((visibility ("default")))
#  else
#    define MY_DLL_API
#  endif

#elif defined __clang__
#  define MY_DLL_API __attribute__ ((visibility ("default")))

#else
#   error "Do not know how to export classes for this platform"
#endif

#endif

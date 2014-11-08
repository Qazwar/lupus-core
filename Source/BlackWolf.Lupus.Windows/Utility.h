#pragma once

#ifdef _MSC_VER
#pragma warning(disable: 4290)
#define NOEXCEPT throw()

#ifdef LUPUSWINDOWS_EXPORT
#define LUPUSWINDOWS_API __declspec(dllexport)
#else
#define LUPUSWINDOWS_API __declspec(dllimport)
#endif

#else
#define NOEXCEPT noexcept

#ifdef LUPUSWINDOWS_EXPORT

#ifdef __CYGWIN__
#define LUPUSWINDOWS_API __attribute__ ((dllexport))
#else
#define LUPUSWINDOWS_API __attribute__ ((visibility ("default")))
#endif

#else

#ifdef __CYGWIN__
#define LUPUSWINDOWS_API __attribute__ ((dllimport))
#else
#define LUPUSWINDOWS_API __attribute__ ((visibility ("default")))
#endif

#endif
#endif

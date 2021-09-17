#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifdef ARIECV_EXPORTS
#define ARIECV_API __declspec(dllexport)
#else
#define ARIECV_API __declspec(dllimport)
#endif
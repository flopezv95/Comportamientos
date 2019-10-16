#ifndef ___LOG___
#define ___LOG___
#include <Windows.h>

#define LOG(msg) OutputDebugStringA(msg "\n");

#endif
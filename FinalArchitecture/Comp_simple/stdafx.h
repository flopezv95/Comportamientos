// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#pragma warning (disable: 4996 4100)

#ifdef _DEBUG
	#include <assert.h>
	#define LEAK_CONTROL
	#define ASSERT(v) assert(v)
#else
	#define ASSERT(V)
#endif

#include "Utils/leaks.h"
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#define RET_ERR 0
#define RET_OK  1

#define SAFE_DELETE(p)				{DEL(p);			 p = NULL;}
#define SAFE_DELETE_ARRAY(p)	{DEL_ARRAY(p); p = NULL;}

// TODO: reference additional headers your program requires here

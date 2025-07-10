#pragma once

#include "VTR_DSS.h"
#include <windows.h>
#include <shellapi.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define WIN32_LEAN_AND_MEAN

VOID DisableScreenSaver()
{
	SetThreadExecutionState(ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED | ES_CONTINUOUS);
}

VOID EnableScreenSaver()
{
	SetThreadExecutionState(ES_CONTINUOUS);
}
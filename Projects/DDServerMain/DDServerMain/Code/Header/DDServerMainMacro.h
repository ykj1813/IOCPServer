#pragma once

#include "Header/DDServerBaseMacro.h"


#if defined(WIN64)
	#define API_DDSERVERMAIN_CLASS    // __declspec(align(8))
	#define API_DDSERVERMAIN_STRUCT   // __declspec(align(8))

#	if defined(DDSERVERBASE_EXPORTS)
		#define API_DDSERVERMAIN         __declspec(dllexport) API_DDSERVERMAIN_CLASS
#	else
		#define API_DDSERVERMAIN         __declspec(dllimport) API_DDSERVERMAIN_CLASS
#	endif

#else
	#define API_DDSERVERMAIN_CLASS    // __declspec(align(4))
	#define API_DDSERVERMAIN_STRUCT   // __declspec(align(4))
	// #define API_DDSERVERMAIN          API_DDSERVERMAIN_CLASS

#	if defined(DDSERVERBASE_EXPORTS)
		#define API_DDSERVERMAIN         __declspec(dllexport) API_DDSERVERMAIN_CLASS
#	else
		#define API_DDSERVERMAIN         __declspec(dllimport) API_DDSERVERMAIN_CLASS
#	endif

#endif

#define API_DDSERVERMAIN_PACKET       __declspec(align(1))


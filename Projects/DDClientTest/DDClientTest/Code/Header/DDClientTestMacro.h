#pragma once

#include "Header/DDServerBaseMacro.h"


#if defined(WIN64)
	#define API_DDCLIENTTEST_CLASS    // __declspec(align(8))
	#define API_DDCLIENTTEST_STRUCT   // __declspec(align(8))


#else
	#define API_DDCLIENTTEST_CLASS    // __declspec(align(4))
	#define API_DDCLIENTTEST_STRUCT   // __declspec(align(4))
	// #define API_DDCLIENTTEST          API_DDCLIENTTEST_CLASS


#endif

#define API_DDCLIENTTEST_PACKET       // __declspec(align(1))


#pragma once

#include "Header/DDCommonMacro.h"

#if defined(DDSERVERDB_EXPORTS)
	#define API_DDSERVERDB         // __declspec(dllexport)

#else
	#define API_DDSERVERDB        //  __declspec(dllimport)

#endif

#if defined(WIN64)
	#define API_DDSERVERDB_CLASS        API_DDSERVERDB // __declspec(align(8))
	#define API_DDSERVERDB_INTERFACE    API_DDSERVERDB // __declspec(align(8))
	#define API_DDSERVERDB_STRUCT       API_DDSERVERDB // __declspec(align(8))


#else
	#define API_DDSERVERDB_CLASS        API_DDSERVERDB // __declspec(align(4))
	#define API_DDSERVERDB_INTERFACE    API_DDSERVERDB // __declspec(align(4))
	#define API_DDSERVERDB_STRUCT       API_DDSERVERDB // __declspec(align(4))

#endif

#define API_DDSERVERDB_PACKET       // __declspec(align(1))


#define CAST_SESSIONID(_Value) static_cast<TSessionId>(_Value)

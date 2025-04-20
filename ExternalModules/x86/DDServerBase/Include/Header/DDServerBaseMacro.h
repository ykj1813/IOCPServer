#pragma once

#include "Header/DDCommonMacro.h"

#if defined(DDSERVERBASE_EXPORTS)
	#define API_DDSERVERBASE         // __declspec(dllexport)

#else
	#define API_DDSERVERBASE        //  __declspec(dllimport)

#endif

#if defined(WIN64)
	#define API_DDSERVERBASE_CLASS        API_DDSERVERBASE // __declspec(align(8))
	#define API_DDSERVERBASE_INTERFACE    API_DDSERVERBASE // __declspec(align(8))
	#define API_DDSERVERBASE_STRUCT       API_DDSERVERBASE // __declspec(align(8))


#else
	#define API_DDSERVERBASE_CLASS        API_DDSERVERBASE // __declspec(align(4))
	#define API_DDSERVERBASE_INTERFACE    API_DDSERVERBASE // __declspec(align(4))
	#define API_DDSERVERBASE_STRUCT       API_DDSERVERBASE // __declspec(align(4))

#endif

#define API_DDSERVERBASE_PACKET       // __declspec(align(1))

#ifndef PURE
	#define PURE =0
#endif // PURE

#define CAST_SESSIONID(_Value) static_cast<TSessionId>(_Value)

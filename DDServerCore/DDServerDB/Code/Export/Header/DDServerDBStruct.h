#pragma once

#include "Header/DDServerDBMacro.h"
#include "Header/DDServerDBEnum.h"
#include "Header/DDServerDBType.h"


template<typename T>
struct FDBProcGetData
{
	FDBProcGetData(T* _Value, size_t _Size = 0)
		: Value(_Value), Size(0 == _Size ? sizeof(T) : _Size), Len(0)
	{

	}

	T* Value;
	size_t Size;
	size_t Len;
};

template<typename T>
struct FDBProcBindPram
{
	FDBProcBindPram(T& _Value, size_t _Size = 0)
		: Value(_Value), Size(0 == _Size ? sizeof(T) : _Size), Len(0)
	{

	}

	T& Value;
	size_t Size;
	size_t Len;
};

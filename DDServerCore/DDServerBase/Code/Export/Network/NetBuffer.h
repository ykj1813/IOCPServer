#pragma once

#include <winsock2.h>
#include <string>


class FNetBuffer
{
public:
	FNetBuffer(size_t BufferSize = 1024);
	FNetBuffer(const FNetBuffer& Instance);
	FNetBuffer(FNetBuffer&& Instance) noexcept;
	/*virtual*/ ~FNetBuffer();

	FNetBuffer& operator=(const FNetBuffer& Instance);
	FNetBuffer& operator=(FNetBuffer&& Instance) noexcept;

	void Clear();

public:
	char* GetBuffer() const;
	size_t WriteBuffer(const char* Data, size_t Length);
	void SetWritePos(size_t Pos);
	size_t GetWritePos() const;
	size_t GetSize() const;

private:
	char* Buffer;
	size_t WriteSize;
	size_t Size;
};


#include "pch.h"
#include "NetBuffer.h"


FNetBuffer::FNetBuffer(size_t BufferSize /*= 1024*/)
	: Size(BufferSize), WriteSize(0)
{
	Buffer = new char[BufferSize];
	ZeroMemory(Buffer, Size);
}

FNetBuffer::FNetBuffer(const FNetBuffer& Instance)
	: Size(Instance.Size), WriteSize(Instance.WriteSize)
{
	Buffer = new char[Instance.Size];
	memcpy(Buffer, Instance.Buffer, Size);
}

FNetBuffer::FNetBuffer(FNetBuffer&& Instance) noexcept
	: Buffer(Instance.Buffer), Size(Instance.Size), WriteSize(Instance.WriteSize)
{
	Instance.Buffer = nullptr;
	Instance.Size = 0;
	Instance.WriteSize = 0;
}

FNetBuffer::~FNetBuffer()
{
	if (nullptr != Buffer)
	{
		delete[] Buffer;
	}
}

FNetBuffer& FNetBuffer::operator=(const FNetBuffer& Instance)
{
	if (this == &Instance)
		return *this;

	SAFE_DELETE_ARRAY(Buffer);

	Size = Instance.Size;
	WriteSize = Instance.WriteSize;
	Buffer = new char[Size];
	memcpy(Buffer, Instance.Buffer, Size);

	return *this;
}

FNetBuffer& FNetBuffer::operator=(FNetBuffer&& Instance) noexcept
{
	if (this == &Instance)
		return *this;

	SAFE_DELETE_ARRAY(Buffer);

	Buffer = Instance.Buffer;
	Size = Instance.Size;
	WriteSize = Instance.WriteSize;

	Instance.Buffer = nullptr;
	Instance.Size = 0;
	Instance.WriteSize = 0;

	return *this;
}

void FNetBuffer::Clear()
{
	if (nullptr != Buffer)
	{
		ZeroMemory(Buffer, Size);
	}
	WriteSize = 0;
}

char* FNetBuffer::GetBuffer() const
{
	return Buffer;
}

size_t FNetBuffer::WriteBuffer(const char* Data, size_t Length)
{
	memcpy(&(Buffer[WriteSize]), Data, Length);
	return (WriteSize += Length);
}

void FNetBuffer::SetWritePos(size_t WritePos)
{
	WriteSize = WritePos;
}

size_t FNetBuffer::GetWritePos() const
{
	return WriteSize;
}

size_t FNetBuffer::GetSize() const
{
	return Size;
}

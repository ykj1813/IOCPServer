#pragma once

#include "Header/DDCommonType.h"
#include "Base/DDServerBaseObject.h"


using TSessionId = int16;
using TPacketMsg = int32;


//:: Using SharedPtr
using DDOverlappedPtr      = std::shared_ptr<struct FDDOverlapped>;
using OverlappedSessionPtr = std::shared_ptr<struct FDDOverlappedSession>;
using SessionPtr           = std::shared_ptr<class CDDIOCPSession>;
using ListenerWorkerPtr    = std::shared_ptr<class CDDIOCPListenerWorker>;


//:: Using UniquePtr
using SessionUPtr = std::unique_ptr<class CDDIOCPSession, CDDServerBaseObjectDeleter>;


//:: Packet

//:: Template
template <typename T>
concept DerivedFromServerBaseObject = std::is_base_of<CDDServerBaseObject, T>::value;

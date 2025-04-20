#pragma once

#include "Header/DDCommonType.h"
#include "Base/DDServerBaseObject.h"


using TSessionId = int16;
using TPacketMsg = int32;
using TNetworkFlag = uint32;
using TSocketError = int32;


//:: Using SharedPtr
using DDOverlappedPtr             = std::shared_ptr<struct FDDOverlapped>;
using DDOverlappedAcceptPtr       = std::shared_ptr<struct FDDOverlappedAccept>;
using DDOverlappedConnectPtr      = std::shared_ptr<struct FDDOverlappedConnect>;
using DDOverlappedDisconnectPtr   = std::shared_ptr<struct FDDOverlappedDisconnect>;
using DDOverlappedSendPtr         = std::shared_ptr<struct FDDOverlappedSend>;
using DDOverlappedRecvPtr         = std::shared_ptr<struct FDDOverlappedRecv>;
using IOCPObjectPtr               = std::shared_ptr<struct CIOCPObject>;
using ListenerPtr                 = std::shared_ptr<class CDDIOCPListener>;
using SessionPtr                  = std::shared_ptr<class CDDIOCPSession>;
using ThreadWorkerPtr             = std::shared_ptr<class CDDIOCPThreadWorker>;
using SessionServerPtr            = std::shared_ptr<class CDDIOCPSessionServer>;
using SessionClientPtr            = std::shared_ptr<class CDDIOCPSessionClient>;
using ListenerWorkerPtr           = std::shared_ptr<class CDDIOCPListenerWorker>;


//:: Using UniquePtr
using SessionUPtr = std::unique_ptr<class CDDIOCPSession, CDDServerBaseObjectDeleter>;


//:: Packet

//:: Template
template <typename T>
concept DerivedFromServerBaseObject = std::is_base_of<CDDServerBaseObject, T>::value;

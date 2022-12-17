#pragma once
#include "pch.h"
#include <asio/ip/tcp.hpp>
#include "SendBuffer.h"
#include "RecvBuffer.h"

using asio::ip::tcp;
using std::move;
using std::shared_ptr;

class AsioSession : public std::enable_shared_from_this<AsioSession>
{
public:
    AsioSession(shared_ptr<asio::io_context> context);
    AsioSession(tcp::socket p_socket);
    virtual ~AsioSession();
    tcp::socket socket;

public:
    void Start() { DoRead(); }
    void Send(shared_ptr<SendBuffer> sendBuffer);
    void Connect(string address, int port);

    void SetOnRecvCallback(function<void(std::shared_ptr<AsioSession>, BYTE*, int32)> callback)
    {
        OnRecvCallback = callback;
    }

    void SetOnDisconnectCallback(function<void(std::shared_ptr<AsioSession>)> callback) { OnDisconnectCallback = callback; }
    void SetOnConnectCallback(function<void(std::shared_ptr<AsioSession>)> callback) { OnConnectCallback = callback; }
    std::shared_ptr<AsioSession> GetSessionRef();

private:
    /* 네트워크 콜백 */
    function<void(std::shared_ptr<AsioSession>, BYTE*, int32)> OnRecvCallback;
    function<void(std::shared_ptr<AsioSession>)> OnDisconnectCallback;
    function<void(std::shared_ptr<AsioSession>)> OnConnectCallback;
    
    void DoRead();
    int  OnRecv(BYTE* buffer, int len);
    void OnConnect();
    void OnDisconnect();

private:
    /* Utility */
    USE_LOCK;

    /* Asio Library */
    //tcp::resolver resolver;

    /* 수신 관련 */
    RecvBuffer recvBuffer;
    int MAX_LENGTH = 0x10000;

    /* 송신 관련 */
    std::queue<shared_ptr<SendBuffer>> sendQueue;
};
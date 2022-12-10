#pragma once
#include <asio/io_context.hpp>
#include "AsioSession.h"

using std::function;
using std::shared_ptr;
using std::vector;

class AsioBaseSocketServer
{
public:
    AsioBaseSocketServer(shared_ptr<asio::io_context> context, int port);

public:
    void StartAccept();
    void DoAccept();
    void RunIoContext();

public:
    void SetOnAcceptCallback(function<void(shared_ptr<AsioSession>)> callback) { onAcceptCallback = callback; }
    void SetOnClientRecv(function<void(shared_ptr<AsioSession>, BYTE*, int32)> callback) { onClientRecv = callback; }
    void SetOnClientDisconnect(function<void(shared_ptr<AsioSession>)> callback) { onClientDisconnect = callback; }

protected:
    function<void(shared_ptr<AsioSession>)> onAcceptCallback;
    function<void(shared_ptr<AsioSession>, BYTE*, int32)> onClientRecv;
    function<void(shared_ptr<AsioSession>)> onClientDisconnect;

private:
    virtual shared_ptr<AsioSession> CreateSession();

private:
    tcp::acceptor acceptor;
    shared_ptr<asio::io_context> ioContext;
};

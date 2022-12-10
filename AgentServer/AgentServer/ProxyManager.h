#pragma once
#include <asio/io_context.hpp>
class ProxyManager
{

public:
    ProxyManager();
    void ConnectToMatchServer();
    void Connect(string address, int port);

private:
    sptr<asio::io_context> ioContext;
    // vector<sptr<>>
};

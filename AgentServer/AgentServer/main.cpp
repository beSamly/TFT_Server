#include "pch.h"
#include "LibraryHeader.h"
#include <iostream>

#include "ServerApp.h"
#include "ProxyManager.h"

int main()
{
    /*sptr<asio::io_context> context = make_shared<asio::io_context>();
    shared_ptr<Proxy> session = make_shared<Proxy>(SERVER_TYPE::MATCH, context);

    session->Connect("127.0.0.1", 4000);
    context->run();*/

    uptr<ServerApp> serverApplication = make_unique<ServerApp>();

    serverApplication->StartNetworkSystem();
    serverApplication->JoinThread();

    return 0;
}
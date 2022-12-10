#include "pch.h"
#include "LibraryHeader.h"
#include <iostream>

#include "ServerApp.h"

int main()
{
    uptr<ServerApp> serverApplication = make_unique<ServerApp>();

    serverApplication->StartSocketServer();
    serverApplication->JoinThread();


    return 0;
}
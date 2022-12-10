#include "pch.h"
#include "LibraryHeader.h"
#include "ServerApp.h"

int main() {


	uptr<ServerApp> serverApplication = make_unique<ServerApp>();

	serverApplication->StartSocketServer();
	serverApplication->StartGameSystem();
	serverApplication->JoinThread();

	return 0;
}
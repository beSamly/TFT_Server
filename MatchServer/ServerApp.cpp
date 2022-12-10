#include "pch.h"
#include "ServerApp.h"
#include "spdlog/spdlog.h"
#include "PacketHeader.h"
#include "TLS.h"

int MAX_WORKER_THREAD = 10;
int NETWORK_TIME_OUT_MS = 1000;
int WORKER_TICK = 64;

ServerApp::ServerApp()
{
	threadSystem = make_shared<ThreadSystem>();
	matchSystem = make_shared<MatchSystem>();
	networkSystem = make_shared<NetworkSystem>(matchSystem);
}

void ServerApp::StartSocketServer()
{
	spdlog::set_level(spdlog::level::debug); // Set global log level to debug

	networkSystem->StartSocketServer();

	// IOCP WorkThread 생성 : 이 프로젝트에서는 IOCP WorkThread가 IOCP 이벤트
	// 처리 후 패킷처리까지 담당
	for (int32 i = 0; i < MAX_WORKER_THREAD; i++)
	{
		threadSystem->Launch(
			[&]()
			{
				while (true)
				{
					//LEndTickCount = ::GetTickCount64() + WORKER_TICK;
					// 네트워크 입출력 및 패킷 핸들러 실행
					networkSystem->RunIoContext();
				}
			});
	}
}

void ServerApp::StartMatchSystem()
{
	//게임시스템 쓰레드
	threadSystem->Launch([&]() { matchSystem->Run(); });
}

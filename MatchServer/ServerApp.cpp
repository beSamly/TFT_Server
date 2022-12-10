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

	// IOCP WorkThread ���� : �� ������Ʈ������ IOCP WorkThread�� IOCP �̺�Ʈ
	// ó�� �� ��Ŷó������ ���
	for (int32 i = 0; i < MAX_WORKER_THREAD; i++)
	{
		threadSystem->Launch(
			[&]()
			{
				while (true)
				{
					//LEndTickCount = ::GetTickCount64() + WORKER_TICK;
					// ��Ʈ��ũ ����� �� ��Ŷ �ڵ鷯 ����
					networkSystem->RunIoContext();
				}
			});
	}
}

void ServerApp::StartMatchSystem()
{
	//���ӽý��� ������
	threadSystem->Launch([&]() { matchSystem->Run(); });
}

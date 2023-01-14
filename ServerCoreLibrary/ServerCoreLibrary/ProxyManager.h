#pragma once

#include <asio/io_context.hpp>
#include "AsioSession.h"

using std::map;
using std::shared_ptr;
using std::vector;

enum SERVER_TYPE : int
{
	NOT_INITIALIZED = 1,
	AGENT,
	MATCH,
	GAME
};

class Proxy : public AsioSession
{
private:
	int serverType;
	string address;
	int port;

public:
	// Proxy(shared_ptr<asio::io_context> ioContext) : serverType(SERVER_TYPE::NOT_INITIALIZED),
	// AsioSession(ioContext){};
	Proxy(SERVER_TYPE type, shared_ptr<asio::io_context> ioContext) : serverType((int)type), AsioSession(ioContext) {};
	Proxy(int type, tcp::socket socket) : serverType(type), AsioSession(std::move(socket)) {};

	SERVER_TYPE GetServerType()
	{
		if (IsAgentServer())
		{
			return SERVER_TYPE::AGENT;
		}
		else if (IsMatchServer())
		{
			return SERVER_TYPE::MATCH;
		}
		else if (IsGameServer())
		{
			return SERVER_TYPE::GAME;
		}
	}
	bool IsAgentServer() { return serverType == (int)SERVER_TYPE::AGENT; }
	bool IsMatchServer() { return serverType == (int)SERVER_TYPE::MATCH; }
	bool IsGameServer() { return serverType == (int)SERVER_TYPE::GAME; }
	void SetConnectionInfo(string p_address, int p_port)
	{
		port = p_port;
		address = p_address;
	}
	string GetAddress() { return address; }
	int GetPort() { return port; }

	void Connect() { AsioSession::Connect(address, port); }

	bool operator==(shared_ptr<Proxy> other) { return other->address == this->address; }
};

class ProxyManager
{
private:
	USE_LOCK;
	shared_ptr<asio::io_context> ioContext;
	std::map<int, vector<shared_ptr<Proxy>>> proxyMap;
	vector<shared_ptr<Proxy>> vecDisconnectedProxy;
	function<void(shared_ptr<Proxy>, BYTE*, int32)> HandleRecv;
	function<void(shared_ptr<Proxy>, SERVER_TYPE)> OnConnectCallback;
	SERVER_TYPE serverType;

public:
	ProxyManager(SERVER_TYPE type);

	void RunIoContext();
	void AddProxy(int type, shared_ptr<Proxy> session);

	void ConnectToMatchServer();
	void ConnectToGameServer();
	void Connect(string address, int port, SERVER_TYPE type);

	bool SendToMatchServer(shared_ptr<SendBuffer> sendBuffer);
	bool SendToGameServer(shared_ptr<SendBuffer> sendBuffer);
	bool SendTo(shared_ptr<SendBuffer> sendBuffer, SERVER_TYPE type);

	void SetHandleRecv(function<void(shared_ptr<Proxy>, BYTE*, int32)> callback) { HandleRecv = callback; };
	void SetOnConnect(function<void(shared_ptr<Proxy>, SERVER_TYPE)> callback) { OnConnectCallback = callback; };

	bool DoReconnect();

private:
	void OnConnect(shared_ptr<AsioSession> session);
	void OnRecv(shared_ptr<AsioSession> session, BYTE* buffer, int len);
	void OnDisconnect(shared_ptr<AsioSession> session);
};

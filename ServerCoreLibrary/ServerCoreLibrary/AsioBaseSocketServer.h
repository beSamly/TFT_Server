#pragma once
#include <asio/io_context.hpp>
#include "AsioSession.h"


using std::shared_ptr;
using std::vector;

class AsioBaseSocketServer
{
public:
	AsioBaseSocketServer(shared_ptr<asio::io_context> context, int port);

public:
	void StartAccept();

	void DoAccept();
	//shared_ptr<asio::io_context> GetContext() { return ioContext; };

private:
	/* 인터페이스 */
	void virtual OnAccept(shared_ptr<AsioSession>) abstract;
	shared_ptr<AsioSession> virtual CreateSession() abstract;
private:
	tcp::acceptor acceptor;
	//shared_ptr<asio::io_context> ioContext;
};

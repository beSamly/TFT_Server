//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "pch.h"
#include "AsioBaseSocketServer.h"

#include <thread>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <asio/ip/tcp.hpp>

using asio::ip::tcp;

AsioBaseSocketServer::AsioBaseSocketServer(shared_ptr<asio::io_context> context, int port) : acceptor(*context, tcp::endpoint(tcp::v4(), port))
{
	/*ioContext = make_shared<asio::io_context>();
	acceptor = tcp::acceptor(*ioContext, );*/
}

void AsioBaseSocketServer::StartAccept() {
	DoAccept();
}

void AsioBaseSocketServer::DoAccept()
{
	shared_ptr<AsioSession> session = CreateSession();

	acceptor.async_accept(session->socket,
		[this, session](std::error_code ec)
		{
			if (!ec)
			{
				OnAccept(session);
				session->Start();
			}

			DoAccept();
		});
}


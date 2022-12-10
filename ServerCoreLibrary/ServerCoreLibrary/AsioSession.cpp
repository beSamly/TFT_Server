#pragma once
#include "pch.h"
#include "AsioSession.h"

//#include <thread>
//#include <cstdlib>
//#include <iostream>
//#include <memory>
//#include <utility>
#include <asio/io_context.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include "asio.hpp"

AsioSession::AsioSession(shared_ptr<asio::io_context> context)
    : socket(*context), resolver(*context), recvBuffer(MAX_LENGTH)
{
}

AsioSession::~AsioSession() {}

void AsioSession::DoRead()
{
    auto self(shared_from_this());
    socket.async_read_some(asio::buffer(recvBuffer.WritePos(), MAX_LENGTH),
                           [this, self](std::error_code ec, std::size_t length)
                           {
                               if (!ec)
                               {
                                   if (recvBuffer.OnWrite(length) == false)
                                   {
                                       // Disconnect(L"OnWrite Overflow");
                                       return;
                                   }

                                   int dataSize = recvBuffer.DataSize();
                                   int processLen = OnRecv(recvBuffer.ReadPos(),
                                                           dataSize); // 컨텐츠 코드에서 재정의
                                   if (processLen < 0 || dataSize < processLen ||
                                       recvBuffer.OnRead(processLen) == false)
                                   {
                                       // Disconnect(L"OnRead Overflow");
                                       return;
                                   }

                                   // 커서 정리
                                   recvBuffer.Clean();

                                   DoRead();
                               }
                               else
                               {
                                   // OnError();

                                   OnDisconnect();
                               }
                           });
}

void AsioSession::Send(shared_ptr<SendBuffer> sendBuffer)
{
    // TODO 일단 write_lock으로 하지만 나중에는 queue로 변경?
    WRITE_LOCK;
    auto self(shared_from_this());
    asio::async_write(socket, asio::buffer(sendBuffer->GetBuffer(), sendBuffer->WriteSize()),
                      [this, self](std::error_code ec, std::size_t /*length*/)
                      {
                          if (!ec)
                          {
                              DoRead();
                          }
                          else
                          {
                              OnDisconnect();
                          }
                      });
}

void AsioSession::Connect(string address, int port)
{
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string(address), port);
    socket.async_connect(ep,
                         [this](const asio::error_code& ec)
                         {
                             if (!ec)
                             {
                                 OnConnect();
                             }
                             else
                             {
                                 std::cout << "connecting error : " << ec << std::endl;
                             }
                         });
}

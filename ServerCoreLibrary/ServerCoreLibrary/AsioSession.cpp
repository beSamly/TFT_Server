#pragma once
#include "pch.h"
#include "AsioSession.h"
#include <asio/io_context.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include "asio.hpp"
#include "PacketHeader.h"

AsioSession::AsioSession(shared_ptr<asio::io_context> context)
    : socket(*context), /*resolver(*context),*/ recvBuffer(MAX_LENGTH)
{
}

AsioSession::AsioSession(tcp::socket p_socket) : socket(std::move(p_socket)), recvBuffer(MAX_LENGTH) {}

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
                                                           dataSize); // ������ �ڵ忡�� ������
                                   if (processLen < 0 || dataSize < processLen ||
                                       recvBuffer.OnRead(processLen) == false)
                                   {
                                       // Disconnect(L"OnRead Overflow");
                                       return;
                                   }

                                   // Ŀ�� ����
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
    // TODO �ϴ� write_lock���� ������ ���߿��� queue�� ����?
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
                                 std::cout << "[AsionSession] connection failed. error = " << ec << std::endl;
                                 OnDisconnect();
                             }
                         });
}

int AsioSession::OnRecv(BYTE* buffer, int len)
{
    int32 processLen = 0;

    while (true)
    {
        int32 dataSize = len - processLen;
        // ������ ����� ��� ������ ���� ���� �� ����
        if (dataSize < sizeof(PacketHeader))
            break;

        PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
        // ����� ��ϵ� ��Ŷ ũ�⸦ �Ľ��� �� �־�� �Ѵ�
        if (dataSize < header.size)
            break;

        // ��Ŷ ���� ����
        OnRecvCallback(shared_from_this(), &buffer[processLen], header.size);
        processLen += header.size;
    }

    return processLen;
}

void AsioSession::OnConnect() { OnConnectCallback(shared_from_this()); }
 
void AsioSession::OnDisconnect() { OnDisconnectCallback(shared_from_this()); }

std::shared_ptr<AsioSession> AsioSession::GetSessionRef() {
    return shared_from_this();
}
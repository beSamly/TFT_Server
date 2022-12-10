#include "pch.h"
#include "ProxyManager.h"

ProxyManager::ProxyManager() { ioContext = make_shared<asio::io_context>(); }

void ProxyManager::ConnectToMatchServer() { Connect("127.0.0.1", 7777); }

void ProxyManager::Connect(string address, int port) {}

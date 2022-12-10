#include "pch.h"
#include "ClientSession.h"
#include "PacketHeader.h"
#include "PacketId_CL_AG.h"
#include "spdlog/spdlog.h"

ClientSession::ClientSession(sptr<asio::io_context> context) : AsioSession(context) {}

ClientSession::~ClientSession() { spdlog::debug("[ClientSession] deconstructed"); }

sptr<Player> ClientSession::GetPlayer() { return player; }

void ClientSession::SetPlayer(sptr<Player> p_player) { player = p_player; }

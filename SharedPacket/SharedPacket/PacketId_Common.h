#pragma once
#pragma once
namespace PacketId_Common {

	enum Prefix : int { AUTH = 1 };

	enum Auth : int {
		PROXY_LOGIN_REQ = 1,
		CLIENT_GAME_SERVER_LOGIN_REQ,
		PROXY_GAME_SERVER_LOGIN_REQ
	};

}  // namespace PacketId_Common

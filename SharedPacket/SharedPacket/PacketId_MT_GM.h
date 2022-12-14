#pragma once

namespace PacketId_MT_GM {

	enum Prefix : int {
		AUTH = 10,
		HOST,
		GAME,
	};

	enum Auth : int {
		LOGIN_REQ = 1,
		LOGIN_RES,
	};

	enum Host : int {
		CREATE_HOST_REQ = 1,
		CREATE_HOST_RES
	};
	enum Game : int { TEST = 1 };

}  // namespace PacketId_MT_GM

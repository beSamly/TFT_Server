#pragma once
#include "IPacketHandler.h"

namespace PacketHandler {
	class Login : public IPacketHandler
	{
	public:
		bool RequireLogin() override { return false; };

		bool Validate(sptr<ClientSession>& session, BYTE* buffer, int32 len) override;

		void HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) override;

	private:
		void HandleFail(sptr<ClientSession>& session, string reason);
	};
}


#include "pch.h"
#include "Login.h"
#include "LoginRequest.pb.h"
#include "LoginResponse.pb.h"
#include "PacketHeader.h"
#include "PlayerManager.h"
#include "InputValidator.h"
#include "PacketId.h"
#include "Packet.h"

bool PacketHandler::Login::Validate(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
	Protocol::LoginRequest pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return false;

	if (!InputValidator::IsEmail(pkt.email())) {
		HandleFail(session, "Invalid Email form");
		return false;
	};

	if (!InputValidator::IsValidPassword(pkt.password())) {
		HandleFail(session, "Invalid authentication info");
		return false;
	};

	return true;
}

void PacketHandler::Login::HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
	Protocol::LoginRequest pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	auto email = pkt.email();
	auto password = pkt.password();
	auto w_email = wstring(email.begin(), email.end());

	// 해당 이메일에 계정이 없을 때
	//if (account == nullptr) {
	//	HandleFail(session, "AccountId does not exist");
	//	return;
	//}

	//// 비밀번호가 틀릴 때
	//if (wstring(password.begin(), password.end()) != account->GetPassword()) {
	//	HandleFail(session, "Invalid authentication info");
	//}

	//auto accountId = account->GetAccountId();
	//PlayerRef player = MakeShared<Player>(accountId);

	
	// Response 보내기
	//Protocol::LoginResponse response;
	//response.set_result(true);

	//Packet packet((int)PacketId::LOGIN_RES);
	//packet.WriteData<Protocol::LoginResponse>(response);
	//session->Send(packet.ToSendBuffer());
}

void PacketHandler::Login::HandleFail(sptr<ClientSession>& session, string reason) {
	Protocol::LoginResponse response;
	response.set_result(false);
	response.set_message(reason);
	//session->SendLoginResponse(response);
	return;
}
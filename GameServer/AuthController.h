#pragma once
#include "IController.h"
#include "ClientSession.h"
#include "TempClientManager.h"

class AuthController : public IController
{
private:
	sptr<TempClientManager> tempClientManager;

public:
	AuthController(sptr<TempClientManager> p_tempClientManager);

private:
	void HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
	void HandleProxyLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};

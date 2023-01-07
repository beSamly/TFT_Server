#pragma once

#include "GameSystem.h"
#include "IController.h"

class HostController : public IController
{
public:
	HostController(sptr<GameSystem> p_gameSystem);

private:
	sptr<GameSystem> gameSystem;
	void HandleHostCreate(sptr<Proxy>& session, BYTE* buffer, int32 len);
};

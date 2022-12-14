#pragma once

#include "GameSystem.h"
#include "IController.h"

class GameController : public IController
{
public:
	GameController(sptr<GameSystem> paramGameSystem);

private:
	sptr<GameSystem> gameSystem;
	void HandleCreateHost(sptr<Proxy>& session, BYTE* buffer, int32 len);
};

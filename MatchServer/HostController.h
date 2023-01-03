#pragma once
#include "IController.h"
#include "MatchSystem.h"

class HostController : public IController
{
private:
	sptr<MatchSystem> matchSystem;

public:
	HostController(sptr<MatchSystem> matchSystem);

private:
	void HandleHostCreateRes(sptr<Proxy>& proxy, BYTE* buffer, int32 len);
};

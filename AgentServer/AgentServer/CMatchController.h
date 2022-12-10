#pragma once
#include "IController.h"

class CMatchController : public IController
{
public:
    CMatchController();

private:
    void HandleMatchRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
    void HandleMatchCancelRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};

#pragma once
namespace PacketId_CL_GM {

enum Prefix : int {
  AUTH = 1,
  DEBUG,
  GAME,
};

enum Auth : int { LOGIN_REQ = 1, LOGIN_RES, LOGOUT_REQ };

enum Debug : int { HOST_CREATE_REQ = 1, GAME_START_REQ };

enum InGame : int { BUY_CHAMP = 1 };

}  // namespace PacketId_CL_GM

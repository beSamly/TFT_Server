#pragma once

namespace PacketId_MT_GM {

enum Prefix : int {
  AUTH = 10,
  GAME,
};

enum Auth : int {
  LOGIN_REQ = 1,
  LOGIN_RES,
};

enum Game : int { CREATE_HOST_REQ = 1 };

}  // namespace PacketId_MT_GM

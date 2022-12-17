#pragma once

namespace PacketId_AG_MT {

enum Prefix : int { AUTH = 1, MATCH };

enum Auth : int { PROXY_LOGIN_REQ = 1 };

enum Match : int {
  MATCH_REQ = 1,
  MATCH_REQ_RES,
  PENDING_MATCH_CREATED_SEND,
  PENDING_MATCH_CANCELED_SEND,
  MATCH_ACCEPT_REQ,
  MATCH_ACCEPT_RES,
  MATCH_CANCEL_REQ,
  MATCH_CANCEL_RES,
  MATCH_CREATED_SEND
};

}  // namespace PacketId_AG_MT
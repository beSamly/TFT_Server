#pragma once

namespace PacketId
{
    enum Prefix : int
    {
        AUTH = 1,
        MATCH,
        IN_GAME,
        DEBUG
    };

    enum Auth : int
    {
        LOGIN_REQ = 1,
        LOGIN_RES,
        LOGOUT_REQ,
    };

    enum Match : int
    {
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

    enum InGame : int
    {
        BUY = 1
    };

    enum Debug : int
    {
        CREATE_DEBUG_MODE_HOST_REQ = 1
    };
} // namespace PacketId

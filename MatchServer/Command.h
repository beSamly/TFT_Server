#pragma once
#include "ProxyManager.h"

namespace Command
{
    class ICommand
    {
    public:
        wptr<Proxy> proxy;
        int commandId;
        int playerId;

    public:
        ICommand() {};
        ICommand(wptr<Proxy> p_proxy, int p_playerId) : playerId(p_playerId), proxy(p_proxy){};
        virtual int GetCommandId() { return commandId; };
    };

    /*-----------------------------------
        NetworkSystem To MatchSystem
    -------------------------------------*/
    namespace N2M {
        enum CommandId
        {
            MATCH_REQUEST = 1,
            MATCH_CANCEL,
            MATCH_ACCEPT,
            MATCH_DECLINE,
        };

        class MatchRequestCommand : public ICommand
        {
        public:
            int matchType;

        public:
            MatchRequestCommand(wptr<Proxy> p_proxy, int p_playerId) : ICommand(p_proxy, p_playerId)
            {
                ICommand::commandId = CommandId::MATCH_REQUEST;
            };
        };

        class MatchCancelCommand : public ICommand
        {
        public:
            int matchType;

        public:
            MatchCancelCommand(wptr<Proxy> p_proxy, int p_playerId) : ICommand(p_proxy, p_playerId)
            {
                ICommand::commandId = CommandId::MATCH_CANCEL;
            };
        };

        class MatchAcceptCommand : public ICommand
        {
        public:
            int matchType;

        public:
            MatchAcceptCommand(wptr<Proxy> p_proxy, int p_playerId) : ICommand(p_proxy, p_playerId)
            {
                ICommand::commandId = CommandId::MATCH_ACCEPT;
            };
        };

        class MatchDeclineCommand : public ICommand
        {
        public:
            int matchType;

        public:
            MatchDeclineCommand(wptr<Proxy> p_proxy, int p_playerId) : ICommand(p_proxy, p_playerId)
            {
                ICommand::commandId = CommandId::MATCH_DECLINE;
            };
        };
        /* Match related - End */
    }

    /* Match related - Begin */




} // namespace Command

#pragma once
#include "ClientSession.h"

namespace Command
{
    class ICommand
    {
    public:
        wptr<ClientSession> client;
        int commandId;

    public:
        ICommand() {};
        ICommand(wptr<ClientSession> p_client) : client(p_client) {};
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
            MatchRequestCommand(wptr<ClientSession> p_client) : ICommand(p_client)
            {
                ICommand::commandId = CommandId::MATCH_REQUEST;
            };
        };

        class MatchCancelCommand : public ICommand
        {
        public:
            int matchType;
            int playerId;

        public:
            MatchCancelCommand(wptr<ClientSession> p_client) : ICommand(p_client)
            {
                ICommand::commandId = CommandId::MATCH_CANCEL;
            };
        };

        class MatchAcceptCommand : public ICommand
        {
        public:
            int matchType;

        public:
            MatchAcceptCommand(wptr<ClientSession> p_client) : ICommand(p_client)
            {
                ICommand::commandId = CommandId::MATCH_ACCEPT;
            };
        };

        class MatchDeclineCommand : public ICommand
        {
        public:
            int matchType;

        public:
            MatchDeclineCommand(wptr<ClientSession> p_client) : ICommand(p_client)
            {
                ICommand::commandId = CommandId::MATCH_DECLINE;
            };
        };
        /* Match related - End */
    }

    /*-----------------------------------
        NetworkSystem To GameSystem
    -------------------------------------*/
    namespace N2G {
        enum CommandId {
            BUY_COMMAND = 1,
        };

        class BuyCommand : public ICommand
        {
        public:
            BuyCommand(wptr<ClientSession> p_client, int p_champUid) : champUid(p_champUid), ICommand(p_client)
            {
                ICommand::commandId = CommandId::BUY_COMMAND;
            };

        public:
            int champUid;
        };

        class LocateToFieldCommand : public ICommand
        {
        public:
            int fieldIndex;

        public:
            LocateToFieldCommand(wptr<ClientSession> p_client, int p_fieldIndex)
                : fieldIndex(p_fieldIndex), ICommand(p_client) {};
        };

        class LocateToBenchCommand : public ICommand
        {
        public:
            int benchIndex;

        public:
            LocateToBenchCommand(wptr<ClientSession> p_client, int p_benchIndex)
                : benchIndex(p_benchIndex), ICommand(p_client) {};
        };

        class CreateDebugModeHostCommand : public ICommand
        {

        public:
            CreateDebugModeHostCommand(wptr<ClientSession> p_client) : ICommand(p_client) {};
        };
    }

    /*-----------------------------------
        MatchSystem To GameSystem
    -------------------------------------*/
    namespace M2G {
        enum CommandId {
            CREATE_HOST,
            CREATE_DEBUG_MODE_HOST,
        };


        class CreateHostCommand : public ICommand
        {
        public:
            vector<wptr<ClientSession>> clientVec;

        public:
            CreateHostCommand(vector<wptr<ClientSession>> p_clientVec) : clientVec(p_clientVec)
            {
                ICommand::commandId = CommandId::CREATE_HOST;
            };
        };
    }

    /* Match related - Begin */




} // namespace Command

/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** protocol
*/

#ifndef PROTOCOL_HPP_
    #define PROTOCOL_HPP_

    namespace protocol {

        #define MAX_MSG_LENGTH  1024

        enum Header {
            PING,
            GAME_INFO,
            PLAYER_ACTION,
            START_GAME,
            EVENT,
            DISCONNECT
        };

    }

#endif /* !PROTOCOL_HPP_ */

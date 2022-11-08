/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** protocol
*/

#ifndef PROTOCOL_H_
    #define PROTOCOL_H_

    namespace protocol {

        #define MAX_MSG_LENGTH  1024

        enum Header {
            PING,
            GAME_INFO,
            PLAYER_ACTION,
            START_GAME,
            EVENT
        };

    }

#endif /* !PROTOCOL_H_ */

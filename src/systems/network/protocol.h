/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** protocol
*/

#ifndef PROTOCOL_H_
    #define PROTOCOL_H_

    namespace protocol {

        enum Header {
            PING,
            GAME_INFO,
            PLAYER_ACTION,
            START_GAME,
            EVENT
        };

        enum Action {
            FIRE,
            MOVE,
            BOTH
        };

    }

#endif /* !PROTOCOL_H_ */

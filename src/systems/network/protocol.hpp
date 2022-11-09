/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** protocol
*/

#ifndef PROTOCOL_HPP_
    #define PROTOCOL_HPP_

    namespace protocol {

        enum Header {
            PING,
            GAME_INFO,
            PLAYER_ACTION,
            START_GAME
        };

        enum Action {
            FIRE,
            MOVE,
            BOTH
        };

    }

#endif /* !PROTOCOL_HPP_ */

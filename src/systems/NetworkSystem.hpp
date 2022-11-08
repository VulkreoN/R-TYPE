/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** NetworkSystem
*/

#ifndef NETWORKSYSTEM_HPP_
    #define NETWORKSYSTEM_HPP_

    #include <asio.hpp>

    #include "ISystem.hpp"
    #include "SceneManager.hpp"
    #include "network/protocol.h"

    #define PRINT_READ_MSG  true    // set to true if you want to print every message the server recieves

    namespace R_TYPE {

        class NetworkSystem : public ISystem {
            public:
                enum class ButtonState : uint8_t {
                    PRESSED,
                    DOWN,
                    RELEASED,
                    UP
                };

                enum class EventType : uint8_t {
                    MOUSE,
                    KEY
                };

                NetworkSystem();
                NetworkSystem(size_t port);
                ~NetworkSystem();

            protected:
                void read_setup();
                virtual void broadcast(SceneManager &) = 0;
                virtual void handle_incomming_message() = 0;
                void putInt(int value, uint8_t buff[], size_t c);
                int readInt(uint8_t buff[], size_t c);
                float readFloat(uint8_t buff[], size_t c);

                // network variables
                asio::io_context _context;
                asio::ip::udp::socket _socket;
                std::thread _threadContext;

                // buffers for reading
                asio::ip::udp::endpoint _edp_buff;
                uint8_t _buffer[1024];
            private:
        };

    }

#endif /* !NETWORKSYSTEM_HPP_ */

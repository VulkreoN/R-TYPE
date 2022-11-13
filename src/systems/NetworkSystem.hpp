/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** NetworkSystem
*/

#ifndef NETWORKSYSTEM_HPP_
    #define NETWORKSYSTEM_HPP_

    #define ASIO_STANDALONE
    #include <asio.hpp>

    #include "ISystem.hpp"
    #include "SceneManager.hpp"
    #include "network/protocol.hpp"

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
                void putInt(int value, std::vector<uint8_t> &buff, size_t c);
                int readInt(const std::vector<uint8_t> &buff, size_t c);
                float readFloat(const std::vector<uint8_t> &buff, size_t c);

                // network variables
                asio::io_context _context;
                asio::ip::udp::socket _socket;
                std::thread _threadContext;

                // buffers for reading
                asio::ip::udp::endpoint _edp_buff;
                std::vector<uint8_t> _buffer;
            private:
        };

    }

#endif /* !NETWORKSYSTEM_HPP_ */

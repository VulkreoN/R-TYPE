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

    #define PRINT_READ_MSG  true    // set to true if you want to print every message the server recieves

    namespace R_TYPE {

        class NetworkSystem : public ISystem {
            public:
                NetworkSystem();
                NetworkSystem(size_t port);
                ~NetworkSystem();

            protected:
                void read_setup();
                virtual void broadcast() = 0;
                virtual void handle_incomming_message() = 0;

                // network variables
                asio::io_context _context;
                asio::ip::udp::socket _socket;
                std::thread _threadContext;

                // buffers for reading
                asio::ip::udp::endpoint _edp_buff;
                char _buffer[1024];
            private:
        };

    }

#endif /* !NETWORKSYSTEM_HPP_ */

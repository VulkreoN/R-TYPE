/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Network
*/

#ifndef ANETWORK_HPP_
    #define ANETWORK_HPP_

    #include <iostream>

    #include "INetwork.hpp"

    class Network {
        public:
            Network(); // write only
            Network(asio::ip::udp::endpoint); // can read and write
            ~Network();
            void write(std::string, asio::ip::udp::endpoint);

        protected:
            void read_setup();
            virtual void handle_incomming_message();

            asio::io_context _context;
            asio::ip::udp::socket _socket;
            std::thread _threadContext;

            // buffers for reading
            asio::ip::udp::endpoint _edp_buff;
            char _buffer[1024];
        private:
    };

#endif /* !ANETWORK_HPP_ */

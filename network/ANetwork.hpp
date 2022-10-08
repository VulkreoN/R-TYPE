/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ANetwork
*/

#ifndef ANETWORK_HPP_
    #define ANETWORK_HPP_

    #include <iostream>

    #include "INetwork.hpp"

    class ANetwork {
        public:
            ANetwork(); // write only
            ANetwork(asio::ip::udp::endpoint); // can read and write
            ~ANetwork();
            void write(std::string, asio::ip::udp::endpoint);

        protected:
            void read_setup();
            asio::io_context _context;
            asio::ip::udp::socket _socket;
            std::thread _threadContext;

            // buffers for reading
            asio::ip::udp::endpoint _edp_buff;
            char _buffer[1024];
        private:
    };

#endif /* !ANETWORK_HPP_ */

/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
    #define CONNECTION_HPP_

    #include "Queue.hpp"
    #include <memory>
    #include <iostream>

    #include <asio.hpp>

    class Connection {
        public:
            Connection(asio::ip::udp::endpoint, size_t);
            ~Connection();
            asio::ip::udp::endpoint get_endpoint();
            size_t get_id();

        protected:
        private:
            asio::ip::udp::endpoint _endpoint;
            size_t _id;
    };

#endif /* !CONNECTION_HPP_ */

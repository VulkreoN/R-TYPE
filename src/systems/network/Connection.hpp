/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
    #define CONNECTION_HPP

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

/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

    #include "INetwork.hpp"
    #include "Connection.hpp"

    #include <memory>

    class Client : INetwork {
        public:
            Client(const std::string ip, const size_t port);
            ~Client();
            void connect();

        protected:
        private:
            std::unique_ptr<Connection> _connection;
            asio::ip::tcp::resolver::results_type _endpoint;
    };

#endif /* !CLIENT_HPP_ */

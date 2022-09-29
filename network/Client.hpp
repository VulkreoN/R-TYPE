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
            void connect(); // connects to a server
            void broadcast(std::string); // sends a message to the server
            void update(); // a function that needs to be called regularly, writes all the messages from write queue

        protected:
        private:
            std::unique_ptr<Connection> _connection;
            asio::ip::tcp::resolver::results_type _endpoint;
            std::thread _threadContext;
    };

#endif /* !CLIENT_HPP_ */

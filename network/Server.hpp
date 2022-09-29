/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include "INetwork.hpp"
    #include "Connection.hpp"

    #include <vector>

    class Server : INetwork {
        public:
            Server(size_t port);
            ~Server();
            void connect(); // a function that once called, accepts all the clients that try to connect
            void broadcast(std::string); // send a message to all players that are connected
            void update(); // a function that needs to be called regularly, writes all the messages from write queues

        protected:
        private:
            std::vector<std::unique_ptr<Connection>> _connections;
            std::thread _threadContext;
            asio::ip::tcp::acceptor _acceptor;
            void accept_client(); // recursive that accepts clients and adds them to _connections
    };

#endif /* !SERVER_HPP_ */

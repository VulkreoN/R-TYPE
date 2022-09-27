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
            void connect();
            void broadcast(std::string);
            void update();

        protected:
        private:
            std::vector<std::unique_ptr<Connection>> _connections;
            std::thread _threadContext;
            asio::ip::tcp::acceptor _acceptor;
            void accept_client();
    };

#endif /* !SERVER_HPP_ */

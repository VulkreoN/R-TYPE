/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include "Network.hpp"
    #include "Connection.hpp"

    #include <vector>

    class Server : Network {
        public:
            Server(size_t port);
            ~Server();
            void handle_incomming_message() override;

        protected:
        private:
            std::vector<std::unique_ptr<Connection>> _connections;
    };

#endif /* !SERVER_HPP_ */

/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

    #include "Network.hpp"
    #include "Connection.hpp"

    #include <memory>

    class Client : Network {
        public:
            Client(const std::string ip, const size_t port);
            ~Client();
            void handle_incomming_message() override;
            void broadcast(std::string) override;

        protected:
        private:
            std::unique_ptr<Connection> _connection;
    };

#endif /* !CLIENT_HPP_ */

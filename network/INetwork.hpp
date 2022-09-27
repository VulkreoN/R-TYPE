/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** INetwork
*/

#ifndef INETWORK_HPP_
    #define INETWORK_HPP_

    #include <asio.hpp>

    class INetwork {
        public:
            ~INetwork() = default;
            virtual void connect() = 0;
            //virtual void run() = 0;
            //virtual void shut_down() = 0;
            virtual void broadcast(std::string) = 0;
            virtual void update() = 0;

        protected:
            // core
            asio::io_context _context;
        private:
    };

#endif /* !INETWORK_HPP_ */

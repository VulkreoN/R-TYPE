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
            virtual void broadcast(std::string) = 0;

        protected:
        private:
    };

#endif /* !INETWORK_HPP_ */

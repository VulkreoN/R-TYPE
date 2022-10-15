/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ServerSystem
*/

#ifndef ServerSystem_HPP_
    #define ServerSystem_HPP_

    #include "NetworkSystem.hpp"
    #include "network/Connection.hpp"

    #define NETWORK_BROADCAST_FREQUENCY  100

    namespace R_TYPE {

        class ServerSystem : public NetworkSystem {
            public:
                ServerSystem(size_t port);
                ~ServerSystem();

                void init(SceneManager &manager) final;
                void update(SceneManager &manager, uint64_t deltaTime) final;
                void destroy() final;

            protected:
            private:
                void handle_incomming_message() final;
                void broadcast() final;

                int _broadcast_cooldown;
                std::vector<std::unique_ptr<Connection>> _connections;
        };

    }

#endif /* !ServerSystem_HPP_ */

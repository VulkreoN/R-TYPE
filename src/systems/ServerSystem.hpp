/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ServerSystem
*/

#ifndef ServerSystem_HPP_
    #define ServerSystem_HPP_

    #include <utility>
    #include "NetworkSystem.hpp"
    #include "network/Connection.hpp"

    #define NETWORK_BROADCAST_FREQUENCY  100

    namespace R_TYPE {

        class EventSystem;

        class ServerSystem : public NetworkSystem {
            public:
                ServerSystem(size_t port);
                ~ServerSystem();

                void init(SceneManager &manager) final;
                void update(SceneManager &manager, uint64_t deltaTime) final;
                void destroy() final;

                const std::vector<std::pair<int, NetworkSystem::ButtonState>> &getKeys() const;
                const std::vector<std::pair<int, NetworkSystem::ButtonState>> &getMouse() const;

            protected:
            private:
                void handle_incomming_message() final;
                void broadcast(SceneManager &) final;

                int _broadcast_cooldown;
                std::vector<std::unique_ptr<Connection>> _connections;
                std::vector<std::pair<int, NetworkSystem::ButtonState>> _keys;
                std::vector<std::pair<int, NetworkSystem::ButtonState>> _mouseButtons;
                std::unique_ptr<EventSystem> eventSystem;

                // functions to create messages to send
                void create_start_game_msg(char *buff, std::unique_ptr<Connection> &connection);
                void create_game_info_msg(char *buff, SceneManager &manager);
        };

    }

#endif /* !ServerSystem_HPP_ */

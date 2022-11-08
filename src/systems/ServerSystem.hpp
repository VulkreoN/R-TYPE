/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ServerSystem
*/

#ifndef ServerSystem_HPP_
    #define ServerSystem_HPP_

    #include <list>
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

                std::list<std::pair<int, NetworkSystem::ButtonState>> getKeys() const;
                std::list<std::pair<int, NetworkSystem::ButtonState>> getMouseButtons() const;
                std::list<std::pair<int, int>> getMousePositions() const;

                void removeKey();
                void removeMouse();

            protected:
            private:
                void handle_incomming_message() final;
                void broadcast(SceneManager &) final;

                int _broadcast_cooldown;
                std::vector<std::unique_ptr<Connection>> _connections;
                std::list<std::pair<int, NetworkSystem::ButtonState>> _keys;
                std::list<std::pair<int, NetworkSystem::ButtonState>> _mouseButtons;
                std::list<std::pair<int, int>> _mousePositions;
                std::unique_ptr<EventSystem> eventSystem;

                // functions to create messages to send
                void create_start_game_msg(char *buff, std::unique_ptr<Connection> &connection);
                void create_game_info_msg(char *buff, SceneManager &manager);
        };

    }

#endif /* !ServerSystem_HPP_ */

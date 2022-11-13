/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ClientSystem
*/

#ifndef CLIENTSYSTEM_HPP_
    #define CLIENTSYSTEM_HPP_

    #include "NetworkSystem.hpp"

    #define NETWORK_PING_FREQUENCY  0

namespace R_TYPE {

    class GraphicSystem;

    class ClientSystem : public NetworkSystem {
        public:
            ClientSystem(std::string ip, size_t port);
            ~ClientSystem() = default;

            void init(SceneManager &manager) final;
            void update(SceneManager &manager, uint64_t deltaTime) final;
            void destroy() final;
            void sendEvent(int button, NetworkSystem::ButtonState state, bool isKey, int x = 0, int y = 0);
            void createProjectile(SceneManager &manager, int id, float x, float y);
            void updateNono(Animation::State state, std::shared_ptr<IEntity> nono);

            size_t _id;

            // functions to create messages to send
            void create_event_msg(std::vector<uint8_t> &buff);

            std::vector<std::vector<uint8_t>> _message_queue;
        protected:
        private:
            void handle_incomming_message() final;
            void broadcast(SceneManager &) final;

            int _ping_cooldown;
            bool firstLaser;
            asio::ip::udp::endpoint _server_endpoint;
            std::unique_ptr<GraphicSystem> graphicSystem;
    };

}

#endif /* !CLIENTSYSTEM_HPP_ */

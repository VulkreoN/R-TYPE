/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
    #define CONNECTION_HPP_

    #include "Queue.hpp"
    #include <memory>
    #include <iostream>

    #include <asio.hpp>

    class Connection {
        public:
            Connection(std::unique_ptr<asio::ip::tcp::socket> socket);
            ~Connection();
            void add_to_write_queue(std::string);
            std::string get_from_read_queue();
            void connect_to_server(const asio::ip::tcp::resolver::results_type& endpoint);
            const std::unique_ptr<asio::ip::tcp::socket> &get_socket() const;

        protected:
        private:
            std::unique_ptr<Queue> _write_queue;
            std::unique_ptr<Queue> _read_queue;
            std::unique_ptr<asio::ip::tcp::socket> _socket;
            // asio::io_context& _asioContext;
            // size_t _id;
    };

#endif /* !CONNECTION_HPP_ */

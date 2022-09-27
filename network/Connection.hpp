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
            std::string get_read_queue();
            void connect_to_server(const asio::ip::tcp::resolver::results_type& endpoint);
            const std::unique_ptr<asio::ip::tcp::socket> &get_socket() const;
            bool check_if_connected();
            void set_connection(bool);
            void check_for_writing();

        protected:
        private:
            std::unique_ptr<Queue> _write_queue;
            std::unique_ptr<Queue> _read_queue;
            std::unique_ptr<asio::ip::tcp::socket> _socket;
            // asio::io_context& _asioContext;
            // size_t _id;
            bool _connected;
            bool _writing;
    };

#endif /* !CONNECTION_HPP_ */

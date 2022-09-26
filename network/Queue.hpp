/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Queue
*/

#ifndef QUEUE_HPP_
    #define QUEUE_HPP_

    #include <string>

    // the queue is currently only for strings, this need to change to binary format
    class Queue {
        public:
            Queue();
            ~Queue();
            void add_to_queue(std::string);
            std::string get_from_queue();

        protected:
        private:
            std::string _content;
    };

#endif /* !QUEUE_HPP_ */

/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Queue
*/

#include "Queue.hpp"

Queue::Queue()
{
}

Queue::~Queue()
{
}

void Queue::add_to_queue(std::string str)
{
    _content.append(str);
}

std::string Queue::get_queue()
{
    return (_content);
}

void Queue::remove_from_queue(size_t size)
{
    if (size >= _content.size())
        _content.clear();
    else
        _content.erase(0, size);
}

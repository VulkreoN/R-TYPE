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

// returns string up to /r/n if there is a /r/n
// if there is no /r/n, returns empty string
std::string Queue::get_from_queue()
{
    std::string ret;
    size_t pos = _content.find("/r/n");

    if (pos == std::string::npos) // return empty string if no /r/n is found
        return (ret);
    ret = _content.substr(0, pos + 2); // return the string up to /r/n
    _content = _content.substr(pos + 2, _content.size()); // remove ret from _content
    return (ret);
}

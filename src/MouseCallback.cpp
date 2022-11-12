#include "MouseCallback.hpp"

namespace R_TYPE
{

    MouseCallback::MouseCallback()
    {
    }

    MouseCallback::MouseCallback(std::function<void(SceneManager &, sf::Vector2i pos)> pressed,
                                 std::function<void(SceneManager &, sf::Vector2i pos)> released):
    _pressed(pressed),
    _released(released)
    {
    }

    MouseCallback::~MouseCallback()
    {
    }
} 
#include "MouseCallback.hpp"

namespace R_TYPE
{

    MouseCallback::MouseCallback()
    {
    }

    MouseCallback::MouseCallback(std::function<void(SceneManager &)> pressed,
                                 std::function<void(SceneManager &)> released):
    _pressed(pressed),
    _released(released)
    {
    }

    MouseCallback::~MouseCallback()
    {
    }
} 
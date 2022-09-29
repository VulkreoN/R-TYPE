#include "ButtonCallback.hpp"

namespace R_TYPE
{

    ButtonCallbacks::ButtonCallbacks()
    {
    }
    ButtonCallbacks::ButtonCallbacks(std::function<void(SceneManager &)> pressed,
                                     std::function<void(SceneManager &)> released):
    pressed(pressed),
          released(released)
    {
    }

    ButtonCallbacks::~ButtonCallbacks()
    {
    }
} 
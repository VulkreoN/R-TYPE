#ifndef MOUSECALLBACK_HPP_
#define MOUSECALLBACK_HPP_

#include <functional>
#include <SFML/System/Vector2.hpp>

namespace R_TYPE
{
    class SceneManager;
    /// @brief Class to group all pressed, released and down callbacks for an event
    class MouseCallback
    {
    public:
        MouseCallback();
        /**
         * @brief Construct a new Button Callbacks object, every callback has a
         *  reference to the scenemenager and a pointer to the entity it should
         *  act on, if any.
         *
         * @param pressed callback to be called when a button is pressed
         * @param released callback to be called when a button is released
         */
        MouseCallback(
            std::function<void(SceneManager &, sf::Vector2i pos)> pressed,
            std::function<void(SceneManager &, sf::Vector2i pos)> released);
        ~MouseCallback();
        std::function<void(SceneManager &, sf::Vector2i pos)> _pressed;
        std::function<void(SceneManager &, sf::Vector2i pos)> _released;

    protected:
    private:
    };
} 

#endif /* !MouseCallback_HPP_ */
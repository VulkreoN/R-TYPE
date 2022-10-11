#ifndef MOUSECALLBACK_HPP_
#define MOUSECALLBACK_HPP_

#include <functional>

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
            std::function<void(SceneManager &)> pressed,
            std::function<void(SceneManager &)> released);
        ~MouseCallback();
        std::function<void(SceneManager &)> _pressed;
        std::function<void(SceneManager &)> _released;

    protected:
    private:
    };
} 

#endif /* !MouseCallback_HPP_ */
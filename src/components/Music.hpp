#ifndef SOUND_HPP
#define SOUND_HPP

#include <SFML/Audio/Music.hpp>
#include "Component.hpp"

namespace R_TYPE {
    class Music : public Component {
        public:
            /// @brief Init Sprite class
            /// @param path Path to init a music
            Music(std::string path);
            ~Music() = default;

            /// @brief Play the sound
            void play();

            /// @brief Stop the sound
            void stop();

            /// @brief Pause the sound
            void pause();

            /// @brief Set the position of the loop
            /// @param start Seconds where to start the loop
            /// @param end Seconds where to end the loop
            void setLoopPoints(int start, int end);

            /// @brief Set if the sound will loop
            void setLoop(bool loop);
        private:
            sf::Music music;
            bool playing;
            bool loop;
    };
}

#endif
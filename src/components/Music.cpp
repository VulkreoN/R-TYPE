#include <iostream>
#include "Music.hpp"

namespace R_TYPE {
    Music::Music(std::string path):
    Component(Component::Type::MUSIC)
    {
        music.openFromFile(path);
    }

    void Music::play()
    {
        //std::cout << "Play the music" << std::endl;
        if (music.getStatus() != sf::SoundSource::Status::Playing)
            music.play();
    }

    void Music::stop()
    {
        //std::cout << "Stop the music" << std::endl;
        music.stop();
    }

    void Music::pause()
    {
        music.pause();
    }

    void Music::setLoopPoints(int start, int end)
    {
        sf::Time _start = sf::seconds(start);
        sf::Time _end = sf::seconds(end);

        music.setLoopPoints(sf::Music::TimeSpan(_start, _end));
    }

    void Music::setLoop(bool loop)
    {
        music.setLoop(loop);
    }
}
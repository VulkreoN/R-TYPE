/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** Animation
*/

#include "Animation.hpp"

namespace R_TYPE {
    Animation::Animation(State state, sf::IntRect rect, int y, int x, int xMax, bool doAction): Component(IComponent::Type::ANIMATION)
    {
        _state = state;
        _rect = rect;
        _y = y;
        _x = x;
        _xMax = xMax;
        _xMin = x;
        _doActions = doAction;
        _nbFrame = _xMin;
    }

    Animation::~Animation()
    {
    }

    void Animation::setRect(sf::IntRect rect)
    {
        _rect = rect;
    }

    void Animation::setState(State state)
    {
        _state = state;
    }

    void Animation::setY(int y)
    {
        _y = y;
    }

    void Animation::setX(int x)
    {
        _x = x;
    }

    void Animation::setXmax(int xMax)
    {
        _xMax = xMax;
    }

    void Animation::setDoActions(bool doActions)
    {
        _doActions = doActions;
    }

    sf::IntRect Animation::getRect()
    {
        return (_rect);
    }

    Animation::State Animation::getState()
    {
        return (_state);
    }

    int Animation::getY()
    {
        return (_y);
    }

    int Animation::getX()
    {
        return (_x);
    }

    int Animation::getXmax()
    {
        return (_xMax);
    }

    bool Animation::getDoActions()
    {
        return (_doActions);
    }

    int Animation::getNbFrame()
    {
        return (_nbFrame);
    }

    int Animation::setNbFrame(int nbFrame)
    {
        _nbFrame = nbFrame;
    }

    void Animation::setCurrentFrame(sf::Time currentFrame)
    {
        _currentFrame = currentFrame;
    }

    sf::Time Animation::getCurrentFrame()
    {
        return (_currentFrame);
    }

    void Animation::restartClock()
    {
        _clock.restart();
    }

    sf::Clock Animation::getClock()
    {
        return(_clock);
    }
}
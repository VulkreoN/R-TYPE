#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

namespace R_TYPE {

    class IEntity;
    class IComponent {
    public:
        enum class Type {
            POSITION,
            VELOCITY,
            TEXT,
            SPRITE,

            HITBOX,
            MUSIC,
            SOUND,
            PLAYER,
            CAMERA,
            ANIMATION,
            PARTICLES,
            PROJECTILES,
            TIMER,
            DESTRUCTIBLE,
            UI,
            TYPE_NB
        };
        virtual const Type &getType() const = 0;
        // virtual bool isInitialized() const = 0;
    };
}
#endif /* ICOMPONENT_HPP */
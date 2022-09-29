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
            EVENT,

            HITBOX,
            MUSIC,
            SOUND,
            PLAYER,
            ANIMATION,
            PARTICLES,
            PROJECTILES,
            DESTRUCTIBLE,
            UI,
            TYPE_NB
        };
        virtual const Type &getType() const = 0;
        // virtual bool isInitialized() const = 0;
    };
}
#endif /* ICOMPONENT_HPP */
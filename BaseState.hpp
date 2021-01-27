//
// Created by Keen on 26.01.2021.
//

#ifndef EVENTS_BASESTATE_HPP
#define EVENTS_BASESTATE_HPP
#include <SFML/Graphics/View.hpp>
class StateManager;

class BaseState {
public:
    explicit BaseState(StateManager* l_stateManager);
    virtual ~BaseState() = default;

    virtual void onCreate() = 0;
    virtual void activate() = 0;
    virtual void deActivate() = 0;
    virtual void destroy() = 0;
    virtual void update(const float& l_dt) = 0;
    virtual void draw() = 0;
    sf::View& get_view() { return m_view; }
    inline bool is_transparent() const { return m_is_transparent; }
    inline bool is_transcendent() const { return m_is_transcendent; }

protected:
    sf::View            m_view;
    StateManager*       m_stateManager;
    bool                m_is_transparent;
    bool                m_is_transcendent;
};


#endif //EVENTS_BASESTATE_HPP

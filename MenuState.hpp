//
// Created by Keen on 26.01.2021.
//

#ifndef EVENTS_MENUSTATE_HPP
#define EVENTS_MENUSTATE_HPP

#include "BaseState.hpp"
class MenuState : public BaseState{
public:
    explicit MenuState(StateManager* l_stateManager);
    void onCreate() override;
    void activate() override;
    void deActivate() override;
    void destroy() override;
    void update(const float &l_dt) override;
    void draw() override;
private:
};


#endif //EVENTS_MENUSTATE_HPP

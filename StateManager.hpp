//
// Created by Keen on 25.01.2021.
//

#ifndef EVENTS_STATEMANAGER_HPP
#define EVENTS_STATEMANAGER_HPP

#include "BaseState.hpp"
#include "SharedContext.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
enum class StateType{
    Global = 0, SplashScreen, Menu, Game, Pause, Quit
};
//vector ensures strict order of states
using States = std::vector<std::pair<StateType, std::unique_ptr<BaseState>>>;
using StateFactory = std::unordered_map<StateType, std::function<std::unique_ptr<BaseState>()>>;

class StateManager {
public:
    StateManager();
    ~StateManager();
    SharedContext* get_shared_context() const { return m_shared_context; }
    void switch_to(StateType l_stateType);
    void remove(StateType l_stateType);
    void set_shared_context(SharedContext* l_shared_context);
    bool has_state(StateType l_stateType);
    void process_removals();
    void update(const float& l_dt);
    void draw();
private:
    bool create(StateType l_stateType);
    void erase(StateType l_stateType);

    template<typename T>
    void register_state(StateType l_stateType);

    States                  m_states;
    StateFactory            m_state_factory;
    std::vector<StateType>  m_to_delete_states;
    SharedContext*          m_shared_context;
};

template<typename T>
void StateManager::register_state(StateType l_stateType) {
    m_state_factory[l_stateType] = [this]()->std::unique_ptr<BaseState>{
        return std::make_unique<T>(this);
    };
}

#endif //EVENTS_STATEMANAGER_HPP

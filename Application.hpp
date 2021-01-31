//
// Created by Keen on 25.01.2021.
//

#ifndef EVENTS_APPLICATION_HPP
#define EVENTS_APPLICATION_HPP

#include "Window.hpp"
#include "SharedContext.hpp"
#include "StateManager.hpp"
#include "TextureManager.hpp"
#include "GUI/GUI_Manager.hpp"

class Application {
public:
    Application();
    Application(Application& l_other) = delete;
    Application& operator=(Application& l_other) = delete;
    void run();

private:
    void update(float l_dt);
    void render();

private:
    SharedContext   m_shared_context;
    Window          m_window;
    StateManager    m_stateManager;
    TextureManager  m_textureManager;
    GUI_Manager     m_gui_manager;
};


#endif //EVENTS_APPLICATION_HPP

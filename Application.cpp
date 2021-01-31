//
// Created by Keen on 25.01.2021.
//

#include "Application.hpp"

Application::Application()
: m_shared_context(), m_window(sf::Vector2u{800,600}),
m_stateManager(), m_textureManager(), m_gui_manager() {

    m_shared_context.m_window = &m_window;
    m_shared_context.m_eventManager = m_window.get_eventManager();
    m_shared_context.m_gui_manager = &m_gui_manager;
    m_shared_context.m_textureManager = &m_textureManager;

    m_stateManager.set_shared_context(&m_shared_context);
    m_gui_manager.set_shared_context(&m_shared_context);

    m_textureManager.request_resource("ADOM_GUI_BACKGROUND");

    m_stateManager.switch_to(StateType::Menu);
    m_stateManager.switch_to(StateType::Game);

}

void Application::run() {
    sf::Clock clock;
    float elapsed = 0;
    float fixed{1.f/60.f};
    while(m_window.is_open()){
        elapsed = clock.restart().asSeconds();
        while(elapsed > fixed){
            elapsed -= fixed;
            update(fixed);
        }
        update(elapsed);
        render();
    }
}

void Application::update(float l_dt) {
    m_window.update();
    GUI_Event gui_event;

    while(m_gui_manager.poll_GUI_event(gui_event)){
        m_window.get_eventManager()->handle_events(gui_event);
    }

    m_stateManager.update(l_dt);
    m_gui_manager.update(l_dt);

    m_stateManager.process_removals();
}

void Application::render() {
    sf::RenderWindow* renderWindow = m_window.get_renderWindow();
    m_window.clear();
    m_stateManager.draw();

    sf::View temp = renderWindow->getView();
    renderWindow->setView(renderWindow->getDefaultView());
    m_gui_manager.draw();
    renderWindow->setView(temp);

    m_window.display();
}
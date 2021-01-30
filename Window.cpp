//
// Created by Keen on 25.01.2021.
//

#include "Window.hpp"


Window::Window(sf::Vector2u l_size) : m_renderWindow(), m_eventManager(), m_size(l_size),
m_is_open(true), m_is_fullScreen(false){
    create_window();
}

void Window::update() {
    sf::Event event{};
    while(m_renderWindow.pollEvent(event)){
        if(event.type == sf::Event::EventType::Closed){
            close();
        }
        m_eventManager.handle_events(event);
    }
    m_eventManager.update();

}

void Window::close() {
    m_is_open = false;
}

void Window::create_window() {
    sf::Uint32 style = m_is_fullScreen ? sf::Style::Fullscreen : sf::Style::Default;
    m_renderWindow.create(sf::VideoMode{m_size.x,m_size.y}, "Events", style);
    m_renderWindow.setKeyRepeatEnabled(false);
}

void Window::toggle_fullscreen([[maybe_unused]] EventDetails *l_details) {
    m_is_fullScreen = !m_is_fullScreen;
    create_window();
}
//
// Created by Keen on 25.01.2021.
//

#ifndef EVENTS_WINDOW_HPP
#define EVENTS_WINDOW_HPP

#include "EventManager.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
class Window {
public:
    explicit Window(sf::Vector2u l_size);
    void update();
    void close();
    inline bool is_open() const { return m_is_open; }
    inline void clear(sf::Color l_color = sf::Color::Black){
        m_renderWindow.clear(l_color);
    }
    inline sf::RenderWindow* get_renderWindow() { return &m_renderWindow; }
    static inline sf::Vector2i getMousePosition([[maybe_unused]] sf::RenderWindow* l_renderWindow = nullptr){
        return l_renderWindow ? sf::Mouse::getPosition(*l_renderWindow) : sf::Mouse::getPosition();
    }
    inline EventManager* get_eventManager() { return &m_eventManager; }
    inline sf::FloatRect get_viewField() const {
        sf::Vector2f center = m_renderWindow.getView().getCenter();
        sf::Vector2f size = static_cast<sf::Vector2f>(m_renderWindow.getSize());
        return sf::FloatRect{
            sf::Vector2f{ center.x - (size.x / 2.f), center.y - (size.y / 2.f) }, // top-left corner
            size }; // size
    }
    inline void display(){
        m_renderWindow.display();
    }
private:
    void create_window();
    void toggle_fullscreen([[maybe_unused]] EventDetails* l_details = nullptr);
private:
    sf::RenderWindow        m_renderWindow;
    EventManager            m_eventManager;
    sf::Vector2u            m_size;
    bool                    m_is_open;
    bool                    m_is_fullScreen;
};


#endif //EVENTS_WINDOW_HPP

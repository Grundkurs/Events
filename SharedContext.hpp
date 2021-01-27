//
// Created by Keen on 26.01.2021.
//

#ifndef EVENTS_SHAREDCONTEXT_HPP
#define EVENTS_SHAREDCONTEXT_HPP

class Window;
class TextureManager;
class EventManager;
class GUI_Manager;

struct SharedContext{
    Window*             m_window = nullptr;
    TextureManager*     m_textureManager = nullptr;
    EventManager*       m_eventManager = nullptr;
    GUI_Manager*        m_gui_manager = nullptr;
};
#endif //EVENTS_SHAREDCONTEXT_HPP

//
// Created by Keen on 31.01.2021.
//

#ifndef EVENTS_TEXTUREMANAGER_HPP
#define EVENTS_TEXTUREMANAGER_HPP

#include "ResourceManager.hpp"
#include <SFML/Graphics/Texture.hpp>

class TextureManager : public ResourceManager<TextureManager, sf::Texture>{
public:
    TextureManager();
private:
    std::unique_ptr<sf::Texture> load(const std::string& l_file_path);
};


#endif //EVENTS_TEXTUREMANAGER_HPP

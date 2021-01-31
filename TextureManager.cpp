//
// Created by Keen on 31.01.2021.
//

#include "TextureManager.hpp"
#include "Utils.hpp"
TextureManager::TextureManager()
: ResourceManager(Utils::get_source_dir() + R"(\resources\config\Textures.cfg)"){

}

std::unique_ptr<sf::Texture> TextureManager::load(const std::string &l_file_path) {
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
    if(!texture->loadFromFile(l_file_path)){
        Logger::get_instance().log("ERROR in TextureManager::load: could not open sf::Texture " + l_file_path);
        throw std::runtime_error("could not load sf::Texture" + l_file_path);
    }
    return std::move(texture);
}

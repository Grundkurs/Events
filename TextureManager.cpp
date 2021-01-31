//
// Created by Keen on 31.01.2021.
//

#include "TextureManager.hpp"
#include "Utils.hpp"
TextureManager::TextureManager()
: ResourceManager(Utils::get_source_dir() + R"(\resources\config\Textures.cfg)"){

}

std::unique_ptr<sf::Texture> TextureManager::load(const std::string &l_file_path) {
    std::unique_ptr<sf::Texture> texture;
    return std::move(texture);
}

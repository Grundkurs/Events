//
// Created by Keen on 28.01.2021.
//

#include "Utils.hpp"
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

std::string Utils::get_source_dir() {
    std::string path = fs::current_path().string();
    std::size_t pos = path.find_last_of('\\');
    if(pos != std::string::npos){
        path = path.substr(0, pos);
    }
    return path;
}

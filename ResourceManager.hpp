//
// Created by Keen on 31.01.2021.
//

#ifndef EVENTS_RESOURCEMANAGER_HPP
#define EVENTS_RESOURCEMANAGER_HPP

#include "Logger.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <sstream>


template<typename DERIVED, typename T>
class ResourceManager{
public:
    explicit ResourceManager(const std::string& l_paths);
    T* get(const std::string& l_resource_name);
    void request_resource(const std::string& l_resource_name);
    void release_resource(const std::string& l_resource_name);

private:
    std::unique_ptr<T> loadResource(const std::string& l_file_path);
    void load_paths(const std::string& l_paths);

    std::unordered_map<std::string, std::pair<int, std::unique_ptr<T>>> m_resources;
    std::unordered_map<std::string, std::string> m_paths;
    std::string m_file_path;
};

template<typename DERIVED, typename T>
ResourceManager<DERIVED, T>::ResourceManager(const std::string &l_paths)
: m_resources(), m_paths(), m_file_path(l_paths){
    load_paths(l_paths);
}

template<typename DERIVED, typename T>
void ResourceManager<DERIVED, T>::load_paths(const std::string &l_paths) {
    std::ifstream file{ l_paths };
    if(!file.is_open()){
        Logger::get_instance().log("Error in ResourceManager::load_paths: could not open file " + l_paths);
        return;
    }
    std::string line{};
    while(std::getline(file, line)){
        if(line.empty()) { continue; }
        if(line[0] == '#') { continue; }
        if(line[0] == '|') { continue; }
        std::stringstream ss { line };
        std::string left{};
        std::string right{};
        ss >> left >> right;
        if(!m_paths.emplace().second){
            std::stringstream tempss{};
            tempss  << "Error in ResourceManager::load_paths: could not add " << left <<" and "
                    << right << " to ResourceManager::m_paths";
            Logger::get_instance().log(tempss.str());
            return;
        }
    }
    file.close();
}

template<typename DERIVED, typename T>
T *ResourceManager<DERIVED, T>::get(const std::string &l_resource_name) {
    return nullptr;
}

template<typename DERIVED, typename T>
void ResourceManager<DERIVED, T>::request_resource(const std::string &l_resource_name) {
    auto found_filePath = m_paths.find(l_resource_name);
    if(found_filePath == m_paths.end()){
        std::stringstream tempss{};
        tempss  << "Error in ResourceManager::request_resource: could not find resource " << l_resource_name
                << " in file " << m_file_path;
        Logger::get_instance().log(tempss.str());
        return;
    }

}

template<typename DERIVED, typename T>
void ResourceManager<DERIVED, T>::release_resource(const std::string &l_resource_name) {

}

template<typename DERIVED, typename T>
std::unique_ptr<T> ResourceManager<DERIVED, T>::loadResource(const std::string &l_file_path) {
    return static_cast<DERIVED*>(this)->load(l_file_path);
}

#endif //EVENTS_RESOURCEMANAGER_HPP

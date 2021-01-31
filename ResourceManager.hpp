//
// Created by Keen on 31.01.2021.
//

#ifndef EVENTS_RESOURCEMANAGER_HPP
#define EVENTS_RESOURCEMANAGER_HPP

#include "Logger.hpp"
#include "Utils.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>


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
        if(!m_paths.emplace(left, right).second){
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
T* ResourceManager<DERIVED, T>::get(const std::string &l_resource_name) {
    auto found_resource_pair = m_resources.find(l_resource_name);
    if(found_resource_pair == m_resources.end()){
        std::stringstream tempss{};
        tempss << R"(Error in ResourceManager::get: could not locate resource ")" << l_resource_name
        << R"(" - resources must be requested with ResourceManager::request_resource(resource_name) before usage)";
        Logger::get_instance().log(tempss.str());
        return nullptr;
    }
    return found_resource_pair->second.second.get();
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
    auto found_resource = m_resources.find(l_resource_name);
    if(found_resource == m_resources.end()){
        auto resource = loadResource(Utils::get_source_dir() + found_filePath->second);
        if(!m_resources.emplace(l_resource_name, std::make_pair(1, std::move(resource))).second){
            std::stringstream tempss{};
            tempss  << R"(Error in ResourceManager::request_resource: could not add resource ")" << l_resource_name
                    << R"( to ResourceManager::m_resources)";
            Logger::get_instance().log(tempss.str());
        }
    }
    else{
        ++found_resource->second.first;
    }
}

template<typename DERIVED, typename T>
void ResourceManager<DERIVED, T>::release_resource(const std::string &l_resource_name) {
    auto found_resource = m_resources.find(l_resource_name);
    if(found_resource == m_resources.end()){
        std::stringstream tempss{};
        tempss  << R"(Error in ResourceManager::release_resource: could not find resource ")" << l_resource_name
                << R"(" to delete in ResourceManager::m_resources)";
        Logger::get_instance().log(tempss.str());
        return;
    }
    if(found_resource->second.first > 1){
        --found_resource->second.first;
    }
    else{
        // when only 1 resource left, erase it completely
        m_resources.erase(found_resource);
    }
}

template<typename DERIVED, typename T>
std::unique_ptr<T> ResourceManager<DERIVED, T>::loadResource(const std::string &l_file_path) {
    return static_cast<DERIVED*>(this)->load(l_file_path);
}

#endif //EVENTS_RESOURCEMANAGER_HPP

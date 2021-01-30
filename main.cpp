//
// Created by Keen on 25.01.2021.
//

#include "Application.hpp"
#include <iostream>
int main(){
    try{
        Application application;
        application.run();
    } catch (const std::exception& e) {
        std::cout << "error: " << e.what() << "\n";
    }
    return 0;
}